#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H
#include <QtWidgets>

//******************************************************************//
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);

    QString getUserName() const;
    QString getPassword() const;
    void setLoginDialogData(QString pass, QString user);

private:
    QLabel *ld_userName;
    QLineEdit *ld_userNameLineEdit;
    QLabel *ld_password;
    QLineEdit *ld_passwordLineEdit;
    QPushButton *ld_loginBtn;
    QPushButton *ld_cancelBtn;
};

#endif // LOGIN_DIALOG_H
//******************************************************************//
