#include "QWidgetPayment.h"
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QTextLayout>
#include <QLabel>
#include "Qt6Identify.h"

QWidgetPayment::QWidgetPayment(QWidget *parent)
    : QObjectPayment(parent)
{

    connect(this,&QObjectPayment::finish,this,&QWidgetPayment::keyboardValue);

    setStyleSheet("background-color: #FFFF00;");
    setTitle("--- 扫码支付 ---");
    setQImageRCode(Qt6Identify::build(),320,320);
    setWelcomeValue("恭喜发财");
}

QWidgetPayment::~QWidgetPayment() {

}

void QWidgetPayment::setTitle(const QString &name)
{
    qstringTitleName=name;
    update();
}

void QWidgetPayment::setWelcomeValue(const QString &text)
{
    qstringWelcomeValue=text;
}

QString QWidgetPayment::getWelcomeValue()
{
    return qstringWelcomeValue;
}

QImage QWidgetPayment::getQImageRCode()
{
    return qimageQRcode;
}


void QWidgetPayment::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QImage canvas(size(), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);

    if(!getWelcomeValue().isEmpty()){
        painter.setFont(QFont("Arial", 62, QFont::Bold));
        painter.setPen(QColor("#FFFACD"));
        QFontMetrics amountFontMetrics(painter.font());
        painter.drawText(canvas.width()/2 - amountFontMetrics.horizontalAdvance(getWelcomeValue())/2,
                         canvas.height()/4,getWelcomeValue());
    }

    if(!getQImageRCode().isNull()){
        painter.drawImage(((canvas.width() - getQImageRCode().width()) / 2),
                          (canvas.height()/2 - getQImageRCode().height()/2),
                          getQImageRCode());
    }

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    QFontMetrics titleFontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - titleFontMetrics.horizontalAdvance(qstringTitleName)/2,
                     canvas.height()/12, qstringTitleName);

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14, QFont::Normal));
    QFontMetrics idfontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - idfontMetrics.horizontalAdvance(Qt6Identify::build())/2,
                     canvas.height()-180, Qt6Identify::build());

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
        update();
    }
}



QImage QWidgetPayment::setQImageRCode(const QString &identify,int width,int height){

    QString qstringURL=  QString("https://wangyonglin.com/pay?deviceid=%1").arg(identify);
    return  qimageQRcode=createPaymentQRCode(qstringURL,QSize(width,height));
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


