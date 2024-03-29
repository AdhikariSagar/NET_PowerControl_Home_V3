#ifndef LOCALIPFINDER_H
#define LOCALIPFINDER_H
#include <QtNetwork>

//******************************************************************//
class LocalIpFinder
{
public:
    static QString find()
    {
        // find out which IP to connect to
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        return ipAddress;
    }
};
#endif // LOCALIPFINDER_H
//******************************************************************//
