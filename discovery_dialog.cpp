#include "discovery_dialog.h"

Discovery_Dialog::Discovery_Dialog(QWidget *parent) : QDialog(parent)
{
    disd_table->setColumnCount(5);
    disd_table->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("IP Address") << tr("IP Mask")<< tr("IP Gateway") << tr("MAC  Address"));

    disd_refreshBtn = new QPushButton(tr("&Refresh"));
    connect(disd_refreshBtn , SIGNAL(clicked()), this, SLOT(onRefresh()));
    //connect(psd_discovery, SIGNAL(discovered()), this, SLOT(onDiscovered()));
    disd_okBtn = new QPushButton(tr("&OK"));
    disd_okBtn->setDisabled(true); // make it default botton
    connect(disd_okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    disd_cancelBtn = new QPushButton(tr("&Cancel"));
    connect(disd_cancelBtn , SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout *discoveryLayout = new QGridLayout(this);
    discoveryLayout->addWidget(disd_table,0,1);
    QBoxLayout* btnlt = new QHBoxLayout();
    btnlt->addStretch(1);
    btnlt->addWidget(disd_okBtn);
    btnlt->addWidget(disd_cancelBtn);
    btnlt->addWidget((disd_refreshBtn));
    discoveryLayout->addLayout(btnlt, 2, 0, 1, 2);

    disd_psdiscovery->onExec();
    connect(disd_table, SIGNAL(itemSelectionChanged()), this, SLOT(onHandelSelection()));
}

void Discovery_Dialog::fillTheTabel()
{
    auto devs = disd_psdiscovery->getDiscoveredDevices();
    disd_table->setRowCount(devs.size());
    for (int i=0; i<devs.size(); ++i)
    {
        auto dev = devs[i];
        disd_table->setItem(i, 0, new QTableWidgetItem(dev.name));
        disd_table->setItem(i, 1, new QTableWidgetItem(dev.ipAddress));
        disd_table->setItem(i, 2, new QTableWidgetItem(dev.ipMask));
        disd_table->setItem(i, 3, new QTableWidgetItem(dev.ipGateaway));
        disd_table->setItem(i, 4, new QTableWidgetItem(dev.macAddress));
    }
}

void Discovery_Dialog::loadTimerIni(const QString &org, const QString &app)
{
    QSettings ini(QSettings::IniFormat, QSettings::UserScope, org, app);
    ini.beginGroup(tr("DEVICE_DELAY_TIMER"));
    int timer = ini.value(tr("timer"), disd_psdiscovery->waitingTimer()).toInt();
    disd_psdiscovery->setTimer(timer);
    ini.endGroup();
}

void Discovery_Dialog::saveTimerIni(const QString &org, const QString &app)
{
    QSettings ini(QSettings::IniFormat, QSettings::UserScope, org, app);
    ini.beginGroup(tr("DEVICE_DELAY_TIMER"));
    int usertimer = disd_psdiscovery->waitingTimer();
    ini.setValue(tr("timer"), usertimer);
    ini.endGroup();
}

PowCtrl_Info Discovery_Dialog::getSelectedDeviceInfo()
{
    return disd_singleDev;
}

/*
 * check the number of devices in discovered devices list
 * if no of device is only one the set the first value of list in singledev(PowCtrl_Info)
 * if not then
 */
void Discovery_Dialog::chooseDevice()
{
    QList<PowCtrl_Info> devs = disd_psdiscovery->getDiscoveredDevices();
    int NoOfDevices = devs.size();
    if(NoOfDevices == 1){
        disd_singleDev = devs[0];
    }
    else {
        fillTheTabel();
        if(this->exec() == QDialog::Accepted){
            devs = disd_psdiscovery->getDiscoveredDevices();
            int r = disd_table->currentRow();
            if (r>=0 && r<devs.size()){
                disd_singleDev = devs[r];
            }
        }
        else{
            disd_singleDev = PowCtrl_Info();
        }
    }
}

void Discovery_Dialog::onRefresh()
{
    disd_psdiscovery->onExec();
    fillTheTabel();
}

void Discovery_Dialog::onHandelSelection()
{
    QList<QTableWidgetSelectionRange> selected_ranges = disd_table->selectedRanges();
    QList<int> selected_rows;
    for (const auto &range : selected_ranges)
    {
        for (int row = range.topRow(); row <= range.bottomRow(); ++row){
            if (!selected_rows.contains(row))
            {
                selected_rows.append(row);
            }
        }
    }
    disd_okBtn->setDisabled(selected_rows.isEmpty());
}
