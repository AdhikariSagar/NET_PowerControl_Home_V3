#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QMessageBox>
#include <power_supply.h>
#include <localipfinder.h>

//******************************************************************//
class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(PowerSupply* ps, QObject*parent = nullptr);

protected Q_SLOTS:
    void onSendFortune();
    void onIncomingClientMessage();
    void onClientMsg();

private:
     QString Buffer;
    PowerSupply* ps = nullptr;
    QList<QTcpSocket*> tcpClientList;
    QTcpServer *tcpServer = new QTcpServer(this);
};

#endif // SERVER_H
//******************************************************************//

