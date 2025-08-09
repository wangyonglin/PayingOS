#include "QObjectPayment.h"
#include <QKeyEvent>

QObjectPayment::QObjectPayment(QWidget *parent)
    : QWidget{parent}
{
    stream=new QTextStream(&data, QIODevice::ReadWrite);
}

QObjectPayment::~QObjectPayment() {

}

void QObjectPayment::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777221){
        emit finish(formatPayment(data.toDouble()));
        data.clear();
        update();
    }
    // 只处理数字键、退格键、小数点
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9 ||
        event->key() == Qt::Key_Backspace ||
        event->key() == Qt::Key_Period ||
        event->key() == Qt::Key_Delete) {
        QWidget::keyPressEvent(event);
        *stream << event->text();
    }
}
QString QObjectPayment::formatPayment(double value) {
    return (qAbs(value - qRound(value)) < 0.005)  // 考虑浮点误差
               ? QString::number(qRound(value))
               : QString::number(value, 'f', 2);
}

QImage QObjectPayment::createPaymentQRCode(const QString& text, const QSize &size){
    QImage dd=generateQRImage(text,size);
    return createCompositeImage(dd,size);
}
QImage QObjectPayment::generateQRImage(const QString& text, const QSize &size) {
    QRcode* qrcode = QRcode_encodeString(text.toUtf8().constData(), 0, QR_ECLEVEL_Q, QR_MODE_8, 1);
    if (!qrcode) return QImage();

    int width = qrcode->width;
    QImage img(width, width, QImage::Format_RGB32);
    img.fill(Qt::white);

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
            if (qrcode->data[y * width + x] & 0x1) {
                img.setPixel(x, y, qRgb(0, 0, 0));
            }
        }
    }

    QRcode_free(qrcode);
    return size.width() > 0 ? img.scaled(size, Qt::KeepAspectRatio) : img;
}

QImage QObjectPayment::createCompositeImage(const QImage& sourceImage, const QSize &size) {
    int backgroundWidth= size.width();
    int backgroundHeight= size.height();

    // 创建目标图像(800x600白色圆角矩形)
    QImage targetImage(backgroundWidth, backgroundHeight, QImage::Format_ARGB32);
    targetImage.fill(Qt::transparent);

    QPainter painter(&targetImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制白色圆角矩形背景
    QRect backgroundRect(0, 0, backgroundWidth, backgroundHeight);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(backgroundRect, 20, 20);

    // 缩放源图像保持比例(最大600x400)
    QImage scaledImage = sourceImage.scaled(
        backgroundWidth/1.4, backgroundHeight/1.4,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    // 计算居中位置
    int x = (backgroundWidth- scaledImage.width()) / 2;
    int y = (backgroundHeight - scaledImage.height()) / 2;

    // 绘制居中图像
    painter.drawImage(x, y, scaledImage);

    // //标题
    // painter.setPen(Qt::red);
    // painter.setFont(QFont("Arial", 30, QFont::Bold));
    // QFontMetrics qfontMetrics(painter.font());
    // painter.drawText(x-qfontMetrics.horizontalAdvance("888")/2,y, "888");

    return targetImage;
}
