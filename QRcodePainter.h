#ifndef QRCODEPAINTER_H
#define QRCODEPAINTER_H

#include <qrencode.h>
#include <QWidget>

class QRcodePainter : public QWidget
{
    Q_OBJECT
public:
    explicit QRcodePainter(QWidget *parent = nullptr);

   static QImage generateQRImage(const QString& text, const QSize &size);
    void loadImage(const QString &text, const QSize & size);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage m_image;
    bool m_antialias = true;
};

#endif // QRCODEPAINTER_H
