#include "server.h"

Server::Server(PowerSupply* ps, QObject *parent) : QObject(parent)
{
    this->ps = ps;
    if (!tcpServer->listen(QHostAddress::Any, 51500)) {
            QMessageBox::critical(nullptr, tr("Fortune Server"),
                                  tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
            return;
        }
    QString ipAddress= LocalIpFinder::find();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onSendFortune);
}

void Server::onSendFortune()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(onClientMsg()));
    tcpClientList.append(clientConnection);
}

void Server::onIncomingClientMessage()
{
    QString buffer;
    QString clientIpAddress;
    int clientPort;
    for (auto TcpSocket:tcpClientList){

          auto data = TcpSocket->readAll();
          buffer += data;
          clientIpAddress = TcpSocket->peerAddress().toString();
          clientPort = TcpSocket->peerPort();
    }
    //qDebug() << QTime::currentTime() << "mybuffer " << buffer << "ipaddress: " << clientIpAddress <<"port:"<<clientPort<<"\n";
    onClientMsg();
}

void Server::onClientMsg()
{
    auto sender_obj = sender();
    auto client = qobject_cast<QTcpSocket*>(sender_obj);
    auto client_msg = client->readAll();
    //qDebug() << "received: " << client_msg;
    Buffer += client_msg;
    if(!Buffer.endsWith("."))
        return;

    //qDebug() << "Buffer complete: "<<Buffer;
    if (Buffer == "start.")
    {
        // do start ...
        client->write("\nHey, Start\n");
        for(int i=0; i< 8; ++i){
           ps->setState(i, true);
        }
    }
    else if (Buffer =="stop.")
    {
        // do stop ?
        client->write("\nHey, Stop\n");
        for(int i=0; i< 8; ++i){
            ps->setState(i, false);
        }
    }
    else {
        client->write("\nnothing\n");
    }
    Buffer.clear();
}
