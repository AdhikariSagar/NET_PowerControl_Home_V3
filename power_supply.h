#ifndef UDP_POWERSUPPLY_H
#define UDP_POWERSUPPLY_H
#include <QtNetwork>

//******************************************************************//
class PowerSupply : public QObject{
    Q_OBJECT
public:
    PowerSupply(QObject*parent=nullptr);

    bool isOn(int i) const;
    QString errorString() const;
    int listeningPort() const;
    int destinationPort() const;
    QHostAddress devAddress() const;
    QString devPass() const;
    QString devUserName() const;
    bool isSocketLocked(int socketPos) const; // locked socket are not available for control
    bool isListening() const;
    void closeListening();
    void setDestination(const QString& address, int port); // device ip and receive port
    void setUserNamePassword(const QString username, QString password);
    bool listen(int port);
    void setState(int i, bool on);
    void sendString(const QString& cmd);

protected Q_SLOTS:
    void onSocketStateChanged();
    void onReadyRead();

Q_SIGNALS:
    void s_stateChanged(int i, bool on);
    void s_connectionStatusChanged(bool connected);
    void s_errorOccured(const QString& msg);
    void s_socketStateChanged();

private:
    QList<bool> p_btnState;
    QUdpSocket* p_socket = new QUdpSocket(this);
    QString p_readBuffer;
    QHostAddress p_targetAddress;
    int p_targetPort;
    QString p_userName;// = "admin";
    QString p_password;// = "anel";
    int p_locked_sockets;

};

//******************************************************************//
#endif // UDP_POWERSUPPLY_H
