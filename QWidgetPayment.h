#ifndef QPaymentWidgetBACK_H
#define QPaymentWidgetBACK_H
#include <QWidget>
#include <QKeyEvent>
#include <QtMqtt/QMqttClient>
#include "QObjectPayment.h"
class QWidgetPayment : public QObjectPayment
{
    Q_OBJECT

public:
    QWidgetPayment(QWidget *parent = nullptr);
    ~QWidgetPayment();

virtual void keyPressEvent(QKeyEvent *event) override;


public slots:
    void keyboardValue(const QString &amount);
    void setTitle(const QString &name);
    void setWelcomeValue(const QString &text);
    QString getWelcomeValue();
    QImage getQImageRCode();
private:
    QImage qimageQRcode;
    QString qstringWelcomeValue="";
    QString qstringTitleName;
    QImage qIconBuilder(const QSize &size);
    QImage setQImageRCode(const QString &identify,int width, int height);
signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;


};
#endif // QPaymentWidgetBACK_H
