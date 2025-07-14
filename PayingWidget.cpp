#include "PayingWidget.h"
#include <QResizeEvent>
#include <QPainter>
PayingWidget::PayingWidget(QWidget *parent)
    : QWidget(parent)
{


    //rcode= new QRcodePainter(parent);
    // rcode->loadImage("wangyonglin",size());
}

PayingWidget::~PayingWidget() {}



void PayingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage image= QRcodePainter::generateQRImage("wang",size());
    if(!image.isNull()){
        QRect imgRect = image.rect();
        imgRect.moveCenter(rect().center());
        painter.drawImage(imgRect, image);
    }

}

void PayingWidget::resizeEvent(QResizeEvent *event)
{
    // rcode->resize(event->size());
    resize(event->size());
}
