#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "power_supply.h"
#include "connection_dialog.h"
#include "login_dialog.h"
#include <QMainWindow>
#include <QSettings>
#include <QtWidgets>

//*********************************************************************************************//
class MainWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindows(PowerSupply* psController, QWidget *parent = nullptr);

    void loadIni(const QString& org, const QString& app);
    void saveIni(const QString& org, const QString& app);
    void handleBtnClick(int btnIndex);
    void UDPStatus(bool connected);
    void loginStatus(bool verified);

protected Q_SLOTS:
    void onBtn1();
    void onBtn2();
    void onBtn3();
    void onBtn4();
    void onBtn5();
    void onBtn6();
    void onBtn7();
    void onBtn8();
    void onDiscover();
    void onLoginAction();
    void onLockedBotton();
    void onPeriodicCheck();
    void onUdpServerAction();
    void onErrorOccured(const QString& msg);
    void onPowerStateChanged(int i, bool on);

Q_SIGNALS:
    void s_btnClicked(int i, bool on);

private:
    QPushButton* m_makeBtn(QString string, const char* slot);
    QList<bool*> m_statusBotton;
    QList<QPushButton*> m_buttonList;
    QTimer m_tmrConnectionCheck;
    QWidget* m_centralWidgetTabel;
    QLabel *m_statusUDP;
    QGridLayout* layoutForBottom;
    QLabel *m_statusLogin = new QLabel(this);
    PowerSupply* m_powerSupplyCtrl = nullptr;
};

#endif // MAINWINDOW_H
//*********************************************************************************************//
