#ifndef DISCOVERY_DIALOG_H
#define DISCOVERY_DIALOG_H
#include <QtWidgets>
#include "powersupplydiscovery.h"

//******************************************************************//
class Discovery_Dialog : public QDialog
{
    Q_OBJECT
public:
     Discovery_Dialog(QWidget*parent=nullptr);

     void fillTheTabel();
     void chooseDevice();
     PowCtrl_Info getSelectedDeviceInfo();
     void loadTimerIni(const QString& org, const QString& app);
     void saveTimerIni(const QString& org, const QString& app);

protected Q_SLOTS:

    void onRefresh();
    void onHandelSelection();

private:

    QTimer disd_delayTime;
    QPushButton *disd_okBtn;
    PowCtrl_Info disd_singleDev;
    QPushButton * disd_cancelBtn;
    QPushButton *disd_refreshBtn;
    QHostAddress disd_deviceAddress;
    QTableWidget* disd_table = new QTableWidget(this);
    PowerSupplyDiscovery* disd_psdiscovery = new PowerSupplyDiscovery(this);
};

#endif // DISCOVERY_DIALOG_H
//******************************************************************//
