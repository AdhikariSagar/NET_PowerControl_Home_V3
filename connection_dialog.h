#ifndef SERVER_DIALOG_H
#define SERVER_DIALOG_H
#include <QtWidgets>

//******************************************************************//
class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectionDialog(QWidget*parent=nullptr);

    void getIPAddress(QString);
    void setDialogData(QString, int, int);
    QString destinationAddress() const;
    int receiveingPort() const;
    int sendingPort() const;

private:
    QLabel *cond_destinationLabel;
    QLineEdit *cond_destinationLineEdit;
    QLabel *cond_sendPortLabel;
    QSpinBox *cond_sendPortLineEdit;
    QLabel *cond_receivePortLabel;
    QSpinBox *cond_receivePortLineEdit;
    QPushButton *cond_okBtn;
    QPushButton *cond_cancelBtn;
};

#endif // SERVER_DIALOG_H
//******************************************************************//
