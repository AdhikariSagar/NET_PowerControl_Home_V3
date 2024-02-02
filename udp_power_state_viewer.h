#ifndef UDP_POWERSUPPLY_H
#define UDP_POWERSUPPLY_H

#endif // UDP_POWERSUPPLY_H
#include <QtWidgets>

class UdpPowerStateViewer : public QWidget
{
    Q_OBJECT
public:
    UdpPowerStateViewer(QWidget* w=nullptr);
    QPushButton* pVi_addBtn(QString status="OFF");
    QList<QPushButton*> pVi_buttonViewerList;


public slots:
    void pVi_onPowerStateChanged(int i, bool on);

};
