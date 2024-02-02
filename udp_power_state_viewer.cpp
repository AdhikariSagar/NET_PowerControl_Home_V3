#include "udp_power_state_viewer.h"



UdpPowerStateViewer::UdpPowerStateViewer(QWidget *w) : QWidget(w)
{
    QGridLayout* lt = new QGridLayout(this);
    for(int i = 0; i<2; ++i){
        for(int j = 0; j<2; ++j){
            lt->addWidget(pVi_addBtn(),i,j);
        }

    }

}

QPushButton *UdpPowerStateViewer::pVi_addBtn(QString status) {
    auto ret = new QPushButton(status, this);
    ret->setEnabled(false);
    ret->setCheckable(true);
    pVi_buttonViewerList << ret;
    return ret;
}

void UdpPowerStateViewer::pVi_onPowerStateChanged(int i, bool on)
{

    auto btn = pVi_buttonViewerList[i];
    btn->setChecked(on);
    btn->setText(on? "ON": "OFF");
}
