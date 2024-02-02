#include "power_supply.h"

PowerSupply::PowerSupply(QObject *parent): QObject(parent) {

    p_btnState << false << false << false << false;
    connect(p_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

bool PowerSupply::isOn(int i) const {
    return p_btnState[i];
}

QString PowerSupply::errorString() const {
    return p_socket->errorString();
}

int PowerSupply::listeningPort() const
{
    return p_socket->localPort();
}

int PowerSupply::destinationPort() const
{
    return p_targetPort;
}

QHostAddress PowerSupply::devAddress() const{
    return p_targetAddress;
}

QString PowerSupply::devPass() const
{
    return p_password;
}

QString PowerSupply::devUserName() const
{
    return p_userName;
}

bool PowerSupply::isSocketLocked(int socketPos) const
{
    int mask = 1 << socketPos;
    return p_locked_sockets & mask;
//    QString bitvalues = QString("%1").arg(Locked_sockets,8,2,QChar('0'));
//    QString reversedString;
//    for (int i = bitvalues.length() - 1; i >= 0; i--)
//            reversedString.append(bitvalues[i]);
//    if(reversedString[socketPos] == '1')
//          return true;
//   return false;
}

bool PowerSupply::isListening() const
{
    return p_socket->state() == QUdpSocket::BoundState;
}

void PowerSupply::closeListening()
{
    p_socket->close();
}

void PowerSupply::setDestination(const QString &address, int port)
{
    p_targetAddress = QHostAddress(address);
    p_targetPort = port;
}

void PowerSupply::setUserNamePassword(const QString username, QString password)
{
    p_userName = username;
    p_password = password;
}

bool PowerSupply::listen(int port)
{
    bool success = p_socket->bind(port);

    sendString("wer da?");
    return success;
}

void PowerSupply::setState(int i, bool on)
{
    QString cmd;
    QString user = p_userName;
    QString pass = p_password;
    bool check = (p_btnState[i] == on);
    if (check)
        return;

    if (on)
        cmd = QString("Sw_on%1%2%3").arg(i+1).arg(user).arg(pass);
    else
        cmd = QString("Sw_off%1%2%3").arg(i+1).arg(user).arg(pass);

    sendString(cmd);
}

void PowerSupply::sendString(const QString &cmd)
{
    p_socket->writeDatagram(cmd.toLatin1()+"\0", p_targetAddress, p_targetPort);
    //u_socket->writeDatagram("wer da?", QHostAddress::Broadcast, 77);
}

void PowerSupply::onSocketStateChanged()
{
    emit s_connectionStatusChanged(isListening());
}

void PowerSupply::onReadyRead()
{
    QString buffer;
    while(p_socket->hasPendingDatagrams()){
        auto datagram = p_socket->receiveDatagram();
        buffer += datagram.data();
    }
    if (buffer.contains("Err")) {
        emit s_errorOccured(buffer.trimmed());
        return;
    }
    QStringList parts = buffer.split(":");
    QStringList statusPort;

    for (int i = 6; i < parts.size() && i<=13; ++i){

            statusPort += parts[i].right(1);
    }
    p_locked_sockets = parts[14].toInt();
    emit s_socketStateChanged();

    for(int j = 0; j < p_btnState.size() && j < statusPort.size(); ++j)
    {
        bool on = statusPort[j].toInt();
        if (p_btnState[j] != on) {
            p_btnState[j] = on;
            emit s_stateChanged(j, on);
        }
    }
    buffer.clear();
}

