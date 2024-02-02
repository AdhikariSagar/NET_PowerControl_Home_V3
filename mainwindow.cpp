#include "mainwindow.h"

MainWindows::MainWindows(PowerSupply* ps, QWidget *parent) : QMainWindow(parent)
{
    m_powerSupplyCtrl = ps;

    m_statusUDP = new QLabel(tr("You need to connect using UDP"));
    //loginStauts = new QLabel(tr("show login status"));

    auto tb = addToolBar(tr("General"));
    //tb->addAction(QIcon(":/lan.jpg"), tr("&Discovery"), this, SLOT(onDiscover()));
    tb->addAction(QIcon(":/lan.jpg"), tr("&Connection"), this, SLOT(onUdpServerAction()));
    tb->addAction(QIcon(":/login.png"), tr("&Login"), this, SLOT(onLoginAction()));

    statusBar()->addPermanentWidget(m_statusLogin, 1);
    statusBar()->addPermanentWidget(m_statusUDP);

    connect(m_powerSupplyCtrl, SIGNAL(s_stateChanged(int, bool)), this, SLOT(onPowerStateChanged(int, bool)));
    connect(m_powerSupplyCtrl, SIGNAL(s_errorOccured(QString)), this, SLOT(onErrorOccured(QString)));
    connect(m_powerSupplyCtrl, SIGNAL(s_socketStateChanged()), this,SLOT(onLockedBotton()));

    m_centralWidgetTabel = new QWidget();
    layoutForBottom = new QGridLayout();
    layoutForBottom->addWidget(m_makeBtn("Botton-1", SLOT(onBtn1())), 4, 0);
    layoutForBottom->addWidget(m_makeBtn("Botton-2", SLOT(onBtn2())), 4, 1);
    layoutForBottom->addWidget(m_makeBtn("Botton-3", SLOT(onBtn3())), 4, 2);
    layoutForBottom->addWidget(m_makeBtn("Botton-4", SLOT(onBtn4())), 4, 3);
    layoutForBottom->addWidget(m_makeBtn("Botton-5", SLOT(onBtn5())), 5, 0);
    layoutForBottom->addWidget(m_makeBtn("Botton-6", SLOT(onBtn6())), 5, 1);
    layoutForBottom->addWidget(m_makeBtn("Botton-7", SLOT(onBtn7())), 5, 2);
    layoutForBottom->addWidget(m_makeBtn("Botton-8", SLOT(onBtn8())), 5, 3);

    m_centralWidgetTabel->setLayout(layoutForBottom);
    setCentralWidget(m_centralWidgetTabel);

    m_tmrConnectionCheck.setInterval(500);
    m_tmrConnectionCheck.start();
    connect(&m_tmrConnectionCheck, SIGNAL(timeout()), this, SLOT(onPeriodicCheck()));
}

void MainWindows::loadIni(const QString &org, const QString &app)
{
    QSettings ini(QSettings::IniFormat, QSettings::UserScope, org, app);
    ini.beginGroup(tr("DEVICE_CONNECTION"));
    QString usr = ini.value(tr("user")).toString();
    QString pass = ini.value(tr("pass")).toString();
    m_powerSupplyCtrl->setUserNamePassword(usr, pass);
    ini.endGroup();
}

void MainWindows::saveIni(const QString &org, const QString &app)
{
    QSettings ini(QSettings::IniFormat, QSettings::UserScope, org, app);
    ini.beginGroup(tr("DEVICE_CONNECTION"));
    QString username = m_powerSupplyCtrl->devUserName();
    QString userpass = m_powerSupplyCtrl->devPass();
    ini.setValue(tr("user"), username);
    ini.setValue(tr("pass"), userpass);
    ini.endGroup();
}

/* check the ctrl is listening or not?
 * if the ctrl is listening, then set the udpstatus label to listening:port
 * else set the udpstatus label to not listening
*/
void MainWindows::onPeriodicCheck()
{
    if (m_powerSupplyCtrl-> isListening()){
        UDPStatus(true);
    }
    else{
        UDPStatus(false);
    }
}

void MainWindows::onLockedBotton()
{
    for(int btnIndex = 0; btnIndex < 8; ++btnIndex){
        auto btn = m_buttonList[btnIndex];
        auto is_locked = m_powerSupplyCtrl->isSocketLocked(btnIndex);
        btn->setEnabled(!is_locked);
    }
}

void MainWindows::onDiscover() {
//    m_discovery->exec();
}

void MainWindows::onUdpServerAction()
{
    ConnectionDialog dlg(this);
    dlg.setDialogData(m_powerSupplyCtrl->devAddress().toString(), m_powerSupplyCtrl->destinationPort(), m_powerSupplyCtrl->listeningPort());

    if (m_powerSupplyCtrl->isListening()){
        //m_statusUDP->setText(tr("Not Listening..."));
        m_powerSupplyCtrl->closeListening();
    }
    if (dlg.exec() == QDialog::Accepted) {
        //m_statusUDP->setText(tr("Listening..."));
        m_powerSupplyCtrl->setDestination(dlg.destinationAddress(), dlg.sendingPort());

        //u_ctrl->u_listen(dlg.receivePort());
        if (m_powerSupplyCtrl->listen(dlg.receiveingPort())) {
            UDPStatus(true);
        }
        else {
            QMessageBox::critical(this, tr("Bind Failed"), m_powerSupplyCtrl->errorString());
            UDPStatus(false);
        }
    }
    else{
        UDPStatus(false);
    }
}

void MainWindows::onLoginAction()
{
    LoginDialog lDialog(this);
    lDialog.setLoginDialogData(m_powerSupplyCtrl->devPass(),m_powerSupplyCtrl->devUserName());
    if(lDialog.exec() == QDialog::Accepted){
        loginStatus(true);
        m_powerSupplyCtrl->setUserNamePassword(lDialog.getUserName(),lDialog.getPassword());
    }
    else{
        loginStatus(false);
    }
}

void MainWindows::onPowerStateChanged(int i, bool on) {
    auto btn = m_buttonList[i];
    btn->setChecked(on);
}

void MainWindows::onErrorOccured(const QString &msg)
{
    QMessageBox::critical(this, tr("Failed"), msg);
}

void MainWindows::UDPStatus(bool connected)
{
    m_statusUDP->setText(connected ? tr("Listening on %1").arg(m_powerSupplyCtrl->listeningPort()) : tr("Offline"));
    QPalette pal;
    pal.setColor(QPalette::WindowText, connected ? Qt::darkGreen : Qt::red);
    m_statusUDP->setPalette(pal);
}

void MainWindows::loginStatus(bool verified)
{
    m_statusLogin->setText(verified ? tr("Loged In"): tr("Please! Enter Username and Password."));
    QPalette palLogIn;
    palLogIn.setColor(QPalette::WindowText, verified ? Qt::blue : Qt::red);
    m_statusLogin->setPalette(palLogIn);
}

void MainWindows::onBtn1()
{
    handleBtnClick(0);
}

void MainWindows::onBtn2()
{
    handleBtnClick(1);
}

void MainWindows::onBtn3()
{
    handleBtnClick(2);
}

void MainWindows::onBtn4()
{
    handleBtnClick(3);

}
void MainWindows::onBtn5()
{
    handleBtnClick(4);
}

void MainWindows::onBtn6()
{
    handleBtnClick(5);
}

void MainWindows::onBtn7()
{
    handleBtnClick(6);
}

void MainWindows::onBtn8()
{
    handleBtnClick(7);

}

void MainWindows::handleBtnClick(int btnIndex)
{
    auto btn = m_buttonList[btnIndex];
    auto is_on = btn->isChecked();
    m_powerSupplyCtrl->setState(btnIndex, is_on);
    btn->setChecked(m_powerSupplyCtrl->isOn(btnIndex));
}

QPushButton *MainWindows::m_makeBtn(QString string, const char* slot)
{
    QFile css(":/style1.css");
    css.open(QFile::ReadOnly);

    QPushButton* Botton = new QPushButton(string, this);
    Botton->setCheckable(true);
    Botton->setStyleSheet(css.readAll());
    Botton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    connect(Botton, SIGNAL(clicked()), this, slot);
    m_buttonList.append(Botton);
    return Botton;
}
