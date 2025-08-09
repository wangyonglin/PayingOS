#include "QWidgetPayment.h"
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QTextLayout>
#include <QLabel>
#include "QUtilConstants.h"

QWidgetPayment::QWidgetPayment(QWidget *parent)
    : QObjectPayment(parent)
{

    connect(this,&QObjectPayment::finish,this,&QWidgetPayment::keyboardValue);

    setStyleSheet("background-color: #FFFF00;");
    setTitle("--- 扫码支付 ---");
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

    if(!qstringAmountValue.isEmpty()){
        painter.setFont(QFont("Arial", 68, QFont::Bold));
        painter.setPen(Qt::white);
        QFontMetrics amountFontMetrics(painter.font());
        qstringAmountValue.prepend("¥ ");
        painter.drawText(canvas.width()/2 - amountFontMetrics.horizontalAdvance(qstringAmountValue)/2,
                         canvas.height()/4,qstringAmountValue);
        qstringAmountValue.clear();
    }

    if(!qimageAmountQRcode.isNull()){
        painter.drawImage(((canvas.width() - qimageAmountQRcode.width()) / 2),
                          (canvas.height()/2 - qimageAmountQRcode.height()/2),
                          qimageAmountQRcode);
    }

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    QFontMetrics titleFontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - titleFontMetrics.horizontalAdvance(qstringTitleName)/2,
                     canvas.height()/12, qstringTitleName);

    painter.drawImage(0,canvas.height()-120,qIconBuilder(QSize(canvas.width(),120)));


}

void QWidgetPayment::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
}

void QWidgetPayment::keyPressEvent(QKeyEvent *event)
{
    QObjectPayment::keyPressEvent(event);
}

void QWidgetPayment::keyboardValue(const QString & amount){
    if(!amount.isEmpty()){
        qimageAmountQRcode= qRCodeBuilder(amount,320,320);
        qstringAmountValue=amount;
        update();
    }
}



QImage QWidgetPayment::qRCodeBuilder(const QString & amount,int width,int height){
    if(!amount.isEmpty()){
        QString qstringURL=  QString("https://wangyonglin.com/wef/ww?deviceid=%1&amount=%2").arg(QUtilConstants::getDeviceId()).arg(amount);
        return  createPaymentQRCode(qstringURL,QSize(width,height));
    }
    return QImage();
}

QImage QWidgetPayment::qIconBuilder(const QSize &size){
    // 创建目标图像(800x600白色圆角矩形)
    QImage targetImage(size, QImage::Format_ARGB32);
    targetImage.fill(Qt::transparent);

    QPainter painter(&targetImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制白色圆角矩形背景
    QRect backgroundRect(0, 0, size.width(),size.height());
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(backgroundRect, 0, 0);

    QImage qimageWechatPay = QImage(":/resources/icon/wechat_pay.png").scaled(
        size.width()/1.6, size.height()/1.6,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    // 计算居中位置
    int xWechatPay = (size.width()/2- qimageWechatPay.width()) / 2;
    int yWechatPay = (size.height() - qimageWechatPay.height()) / 2;

    // 绘制居中图像
    painter.drawImage(xWechatPay, yWechatPay, qimageWechatPay);

    QImage qimageAliPay = QImage(":/resources/icon/alipay.png").scaled(
        size.width()/1.6, size.height()/1.6,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    // 计算居中位置
    int xAliPay = (size.width())/2;
    int yAliPay = (size.height() - qimageAliPay.height()) / 2;

    // 绘制居中图像
    painter.drawImage(xAliPay, yAliPay, qimageAliPay);
    return targetImage;
}
