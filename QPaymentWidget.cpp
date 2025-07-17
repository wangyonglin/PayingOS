#include "QPaymentWidget.h"
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>

QPaymentWidget::QPaymentWidget(QWidget *parent)
    : QPaymentObject(parent)
{
    connect(this,&QPaymentObject::finish,this,&QPaymentWidget::keyboardValue);
    setStyleSheet("background-color: #027AFF;");

    thisTitleValue="常熟瓜王";
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
    QImage canvas(width(), height(), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);

    //标题
    painter.setPen(Qt::white);  // 设置文本颜色‌:ml-citation{ref="6" data="citationList"}
    painter.setFont(QFont("Arial", 30, QFont::Bold));  // 设置字体及大小‌:ml-citation{ref="6,8" data="citationList"}
    QFontMetrics fm(painter.font());
    int textWidth = fm.horizontalAdvance(thisTitleValue);  // ‌:ml-citation{ref="4" data="citationList"}
    painter.drawText(width()/2 - textWidth/2, height()/16, thisTitleValue);  // ‌:ml-citation{ref="4,5" data="citationList"}
    //

    // 绘制居中图片


    // if(!thisAmountValue.isEmpty()){
    //     painter.drawText(0,0,thisAmountValue);
    // }

    if(!thisAmountQRcode.isNull()){
        int logoX = (canvas.width() - thisAmountQRcode.width()) / 2;
        int logoY = (canvas.height()/2 - thisAmountQRcode.height()/2);
        painter.drawImage(logoX, logoY, thisAmountQRcode);
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
        thisAmountValue=amount;
        update();
    }
}


