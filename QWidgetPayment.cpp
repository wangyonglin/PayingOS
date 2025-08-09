#include "QPaymentWidget.h"
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>

QPaymentWidget::QPaymentWidget(QWidget *parent)
    : QPaymentObject(parent)
{
    connect(this,&QPaymentObject::finish,this,&QPaymentWidget::keyboardValue);
    setStyleSheet("background-color: #027AFF;");
    thisTitleValue="支付页面";

}

QPaymentWidget::~QPaymentWidget() {

}

void QPaymentWidget::setTitleName(const QString &name)
{
    thisTitleValue=name;
}


void QPaymentWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage canvas(size(), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    QFontMetrics titleFontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - titleFontMetrics.horizontalAdvance(thisTitleValue)/2, canvas.height()/12, thisTitleValue);  // ‌:ml-citation{ref="4,5" data="citationList"}
    //

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

void QPaymentWidget::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
}

void QPaymentWidget::keyPressEvent(QKeyEvent *event)
{
    QPaymentObject::keyPressEvent(event);
}

void QPaymentWidget::keyboardValue(const QString & amount){
    if(!amount.isEmpty()){
        thisAmountQRcode =  createPaymentQRCode(amount,QSize(300,300));
        qDebug() << amount;
        thisAmountValue=amount;
        update();
    }
}


