#include "login_dialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog (parent)
{
    ld_userName = new QLabel(tr("&User Name:"));
    ld_userNameLineEdit = new QLineEdit("admin");
    ld_userName->setBuddy(ld_userNameLineEdit);

    ld_password = new QLabel(tr("&Password:"));
    ld_passwordLineEdit = new QLineEdit("anel");
    ld_password->setBuddy(ld_passwordLineEdit);

    ld_loginBtn = new QPushButton(tr("Login"));
    ld_loginBtn->setDefault(true); // make it default botton
    connect(ld_loginBtn, SIGNAL(clicked()), this, SLOT(accept()));

    ld_cancelBtn = new QPushButton(tr("Cancel"));
    connect(ld_cancelBtn , SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout* loginLayout = new QGridLayout(this);
    loginLayout->addWidget(ld_userName, 0, 0);
    loginLayout->addWidget(ld_userNameLineEdit, 0, 1);
    loginLayout->addWidget(ld_password, 1, 0);
    loginLayout->addWidget(ld_passwordLineEdit, 1, 1);

    QBoxLayout* btnList = new QHBoxLayout();
    btnList->addStretch(1);
    btnList->addWidget(ld_loginBtn);
    btnList->addWidget(ld_cancelBtn);
    loginLayout->addLayout(btnList, 2, 0, 1, 2);
}

QString LoginDialog::getUserName() const
{
    return ld_userNameLineEdit->text();
}
QString LoginDialog::getPassword() const {

    return ld_passwordLineEdit->text();
}

void LoginDialog::setLoginDialogData(QString pass, QString user)
{
    ld_userNameLineEdit->setText(user);
    ld_passwordLineEdit->setText(pass);
}
