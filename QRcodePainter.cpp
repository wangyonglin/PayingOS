#include "QRcodePainter.h"
#include <QPainter>
#include <QPen>
#include <QResizeEvent>
#include <QSize>
QRcodePainter::QRcodePainter(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
}

void QRcodePainter::loadImage(const QString& text, const QSize &size) {
    m_image=generateQRImage(text,size);
    if(!m_image.isNull()) {

        update();
    }
}

void QRcodePainter::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // 设置抗锯齿
    if(m_antialias) {
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
    }

    // 绘制背景
    painter.fillRect(rect(), Qt::white);

    if(!m_image.isNull()) {
        // 居中显示图像
        QRect imgRect = m_image.rect();
        imgRect.moveCenter(rect().center());
        painter.drawImage(imgRect, m_image);
    }

    // 在图像上叠加绘制图形
    QPen pen(Qt::red, 3);
    painter.setPen(pen);
    painter.drawEllipse(rect().center(), 50, 50);  // 绘制圆形
    painter.drawLine(rect().topLeft(), rect().bottomRight());  // 绘制对角线
}


QImage QRcodePainter::generateQRImage(const QString& text, const QSize &size) {
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
