#ifndef QPaymentWidgetBACK_H
#define QPaymentWidgetBACK_H
#include <QWidget>
#include <QKeyEvent>
#include <QtMqtt/QMqttClient>
#include "QPaymentObject.h"
class QWidgetPayment : public QPaymentObject
{
    Q_OBJECT

public:
    QWidgetPayment(QWidget *parent = nullptr);
    ~QWidgetPayment();

public slots:
    void keyboardValue(const QString &amount);
    void setTitle(const QString &name);
private:
    QImage thisAmountQRcode;
    QString thisAmountValue;
    QString qstringTitleName;

signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

};
#endif // QPaymentWidgetBACK_H
