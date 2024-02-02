#include "connection_dialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) : QDialog(parent)
{
    cond_destinationLabel = new QLabel(tr("&Destination Address:"));
    cond_destinationLineEdit = new QLineEdit(this);
    cond_destinationLabel->setBuddy(cond_destinationLineEdit);
    cond_receivePortLabel = new QLabel(tr("&Receiving  Port:"));
    cond_receivePortLineEdit = new QSpinBox;
    cond_receivePortLineEdit->setRange(1, 65535);
    cond_receivePortLabel->setBuddy(cond_receivePortLineEdit);
    cond_sendPortLabel = new QLabel(tr("&Destination Port:"));
    cond_sendPortLineEdit = new QSpinBox;
    cond_sendPortLineEdit->setRange(1, 65535);
    cond_sendPortLabel->setBuddy(cond_sendPortLineEdit);

    cond_okBtn = new QPushButton(tr("OK"));
    cond_okBtn->setDefault(true); // make it default botton
    connect(cond_okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    cond_cancelBtn = new QPushButton(tr("Cancel"));
    connect(cond_cancelBtn , SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout* layout_server = new QGridLayout(this);
    layout_server->addWidget(cond_destinationLabel, 0, 0);
    layout_server->addWidget(cond_destinationLineEdit, 0, 1);
    layout_server->addWidget(cond_sendPortLabel, 1, 0);
    layout_server->addWidget(cond_sendPortLineEdit, 1, 1);
    layout_server->addWidget(cond_receivePortLabel, 2, 0);
    layout_server->addWidget(cond_receivePortLineEdit, 2, 1);

    QBoxLayout* btnlt = new QHBoxLayout();
    btnlt->addStretch(1);
    btnlt->addWidget(cond_okBtn);
    btnlt->addWidget(cond_cancelBtn);
    layout_server->addLayout(btnlt, 3, 0, 1, 2);
}

void ConnectionDialog::setDialogData(QString ipAddress, int devPort, int receivePort)
{
    cond_destinationLineEdit->setText(ipAddress);
    cond_sendPortLineEdit->setValue(devPort);
    cond_receivePortLineEdit->setValue(receivePort);
}

QString ConnectionDialog::destinationAddress() const {
    return cond_destinationLineEdit->text();
}

int ConnectionDialog::receiveingPort() const {
    return cond_receivePortLineEdit->value();
}

int ConnectionDialog::sendingPort() const {
    return cond_sendPortLineEdit->value();
}


