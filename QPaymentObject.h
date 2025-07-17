#ifndef QPAYMENTOBJECT_H
#define QPAYMENTOBJECT_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothAddress>
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceInfo>
#include <QRegularExpressionValidator>
#include <QMap>
#include <QDebug>
#include <qrencode.h>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QLineEdit>
#include <QTextStream>



class QPaymentObject : public QWidget
{
    Q_OBJECT
public:
    explicit QPaymentObject(QWidget *parent = nullptr);
    ~QPaymentObject();
signals:
    void finish(const QString & amount);
public slots:
public:
    virtual void keyPressEvent(QKeyEvent *event) override;

    QImage createPaymentQRCode(const QString &text, const QSize &size);
private:
    int fontSize=16;
    QColor fontColor;
    QString data;
    QTextStream *stream;
    QString formatPayment(double value);
    QImage createCompositeImage(const QImage &sourceImage);
    QImage generateQRImage(const QString &text, const QSize &size);
};

#endif // QPAYMENTOBJECT_H
