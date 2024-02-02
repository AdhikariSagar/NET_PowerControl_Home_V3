#include "powersupplydiscovery.h"

PowerSupplyDiscovery::PowerSupplyDiscovery(QObject *parent) : QObject(parent)
{
    // the socket can receive incoming UDP datagrams.
    // m_socket will listen for incoming UDP datagrams on the specified IP address and port number.
    psd_socket->bind(QHostAddress(LocalIpFinder::find()), 77);
    connect(psd_socket, SIGNAL(readyRead()), this, SLOT(onReadIncoming()));
}

QList<PowCtrl_Info> PowerSupplyDiscovery::getDiscoveredDevices() const{

    return psd_discoveredDevices;
}

/*
 * sending a UDP datagram containing the string "wer da?" to all hosts on the local network,
 * using port number 75 of the receiving endpoint(device receiveport).
 */
void PowerSupplyDiscovery::onExec()
{
    psd_discoveredDevices.clear();
    psd_socket->writeDatagram("wer da?", QHostAddress::Broadcast, 75);

    QTime time;
    time.start();
//    while(time.elapsed()< delayTime && m_discoveredDevices.size() <= 1){
//            m_socket->waitForReadyRead(100);
//        }
    while(time.elapsed()< psd_delayTime ){ //test
        if (psd_discoveredDevices.size() > 1){
            break;
        }
        psd_socket->waitForReadyRead(100);
    }
}

void PowerSupplyDiscovery::onReadIncoming()
{
    QString buffer;
    while(psd_socket->hasPendingDatagrams()){
        auto datagram = psd_socket->receiveDatagram();
        buffer += datagram.data();
    }
    auto dev_info_list = buffer.split("\r\n", QString::SkipEmptyParts);
    for (auto dev_buf : dev_info_list)
    {
        PowCtrl_Info discovered_dev = extractFromString(dev_buf);
        addDevices(discovered_dev );
    }
//    addDevice(PowCtrl_Info{"fake dev 1", "local1", "", "", ""});
//    addDevice(PowCtrl_Info{"fake dev 2", "", "", "", ""});
//    emit discovered();
//    m_discoveredDevices.clear();
}

PowCtrl_Info PowerSupplyDiscovery::extractFromString(const QString &str)
{
    QStringList parts = str.split(":");
    PowCtrl_Info dev;
    dev.name = parts[1];
    dev.ipAddress = parts[2];
    dev.ipMask = parts[3];
    dev.ipGateaway = parts[4];
    dev.macAddress = parts[5];
    return dev;
}

void PowerSupplyDiscovery::addDevices(const PowCtrl_Info &dev)
{
    if (!isAlreadyDiscovered(dev.ipAddress))
    {
        psd_discoveredDevices << dev;
    }
}

bool PowerSupplyDiscovery::isAlreadyDiscovered(const QString &ip) const
{
    for (auto device : psd_discoveredDevices){
        if(device.ipAddress == ip){
            return true;
        }
    }
    return  false;
}

int PowerSupplyDiscovery::waitingTimer() const{
    return psd_delayTime;
}

void PowerSupplyDiscovery::setTimer(const int timer)
{
    if (timer > 0 && timer <10000) {
        psd_delayTime = timer;
    }
}
