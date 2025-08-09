#include "QWidgetPayment.h"
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>


QWidgetPayment::QWidgetPayment(QWidget *parent)
    : QPaymentObject(parent)
{

    connect(this,&QPaymentObject::finish,this,&QWidgetPayment::keyboardValue);
    setStyleSheet("background-color: #027AFF;");
    setTitle("QWidgetPayment");
}

QWidgetPayment::~QWidgetPayment() {

}

void QWidgetPayment::setTitle(const QString &name)
{
    qstringTitleName=name;
    update();
}


void QWidgetPayment::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage canvas(size(), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    QFontMetrics titleFontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - titleFontMetrics.horizontalAdvance(qstringTitleName)/2,
                     canvas.height()/12, qstringTitleName);



    // 绘制居中图片


    if(!thisAmountValue.isEmpty()){
        painter.setFont(QFont("Arial", 64, QFont::Bold));
        painter.setPen(Qt::red);
        QFontMetrics amountFontMetrics(painter.font());
        thisAmountValue.prepend("¥ ");
        painter.drawText(canvas.width()/2 - amountFontMetrics.horizontalAdvance(thisAmountValue)/2, canvas.height()/4.5,thisAmountValue);
        thisAmountValue.clear();
    }

    if(!thisAmountQRcode.isNull()){
        painter.drawImage( ((canvas.width() - thisAmountQRcode.width()) / 2), (canvas.height()/2 - thisAmountQRcode.height()/2), thisAmountQRcode);
    }
}

void QWidgetPayment::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
}

void QWidgetPayment::keyPressEvent(QKeyEvent *event)
{
    QPaymentObject::keyPressEvent(event);
}

void QWidgetPayment::keyboardValue(const QString & amount){
    if(!amount.isEmpty()){
        thisAmountQRcode =  createPaymentQRCode(amount,QSize(300,300));
        qDebug() << amount;
        thisAmountValue=amount;
        update();
    }
}



