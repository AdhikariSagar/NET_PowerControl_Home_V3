#ifndef POWERSUPPLYDISCOVERY_H
#define POWERSUPPLYDISCOVERY_H

#include <localipfinder.h>
#include "powercontrolinfo.h"

//******************************************************************//
class PowerSupplyDiscovery : public QObject
{
    Q_OBJECT
public:
    explicit PowerSupplyDiscovery(QObject *parent = nullptr);

    int waitingTimer() const;
    void setTimer(const int timer);
    void addDevices(const PowCtrl_Info& dev);
    bool isAlreadyDiscovered(const QString& ip) const;
    QList<PowCtrl_Info> getDiscoveredDevices() const;
    static PowCtrl_Info extractFromString(const QString& str);

Q_SIGNALS:
    void s_discovered();

public Q_SLOTS:
    void onExec();
    void onReadIncoming();

private:
    QUdpSocket* psd_socket = new QUdpSocket(this);
    QList<PowCtrl_Info> psd_discoveredDevices;
    int psd_delayTime = 1000;
};

#endif // POWERSUPPLYDISCOVERY_H
//******************************************************************//
