#include "mainwindow.h"
#include "power_supply.h"
#include <QApplication>
#include <QString> // working with strings
#include <QWidget>
#include <discovery_dialog.h>
#include <server.h>

PowCtrl_Info getDeviceInfo(QString org, QString app)
{
    Discovery_Dialog dlg;
    dlg.resize(550,140);
    dlg.setWindowTitle("Discoverd Devices");
    dlg.loadTimerIni(org, app);
    dlg.chooseDevice();
    dlg.saveTimerIni(org, app);
//    if (dlg.exec() != QDialog::Accepted) { // if you dont accept the Dialog  then it will close the programm
//        return PowCtrl_Info();
//    }
    auto dev = dlg.getSelectedDeviceInfo();
    return dev;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationDisplayName(("BottonStatus"));
    QString org = QString("iLA_5150");
    QString app = QString("PowerControl");

    QFile file("C:/Users/PIVview/Documents/NET_PowerControl_Home_V3/17.json");
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();

    QJsonParseError errPar;
    QJsonDocument doc = QJsonDocument::fromJson(ba, &errPar);
    QString errstr = errPar.errorString();
    QJsonObject obj = doc.object();

    QStringList keys = obj.keys();
    QMap<QString,QVariant> dataMap;

    for (const QString &k : keys){
         const QJsonValue &jsonVal = obj.value(k);
         if(jsonVal.isNull()){
            dataMap.insert(k,"null");
         }
         else if(jsonVal.isUndefined()){
            dataMap.insert(k,"undef");
         }
         else if(jsonVal.isBool()){
             bool val = jsonVal.toBool();
             dataMap.insert(k,val);

         }
         else {
             QVariant values = jsonVal.toVariant();
             dataMap.insert(k,values);
         }

     }


    // step 1 discover the device
    auto dev = getDeviceInfo(org, app);

    // step 2 check discoverd the device's ip address
    bool was_canceled_by_user = dev.ipAddress.isEmpty();
    if (was_canceled_by_user)
        return -1;

    // step 3 call powersupply with discovered device ip addresse and it's  receiving port and sending port
    PowerSupply* ps = new PowerSupply();
    ps->setDestination(dev.ipAddress, 75);
    ps->listen(77);

    // step 4 start sever
    Server* ps_service = new Server(ps);

    // step 5 call mainwindow with server
    MainWindows w(ps);
    w.resize(700,500);
    //w.setWindowTitle("You are Opening our: ");

    w.loadIni(org, app);
    w.show();

    int exec_code = a.exec();
    w.saveIni(org, app);
    // do post routines

    return exec_code;
}
