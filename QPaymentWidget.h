#ifndef QPAYMENTWIDGET_H
#define QPAYMENTWIDGET_H
#include <QWidget>
#include <QKeyEvent>
#include "QPaymentObject.h"

class QPaymentWidget : public QPaymentObject
{
    Q_OBJECT

public:
    QPaymentWidget(QWidget *parent = nullptr);
    ~QPaymentWidget();

    QImage createCompositeImage(const QImage &sourceImage);
public slots:
    void setTitleName(const QString &name);
    void keyboardValue(const QString &amount);
private:
    QImage thisAmountQRcode;
    QString thisAmountValue;
    QString thisTitleValue;
signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

};
#endif // QPAYMENTWIDGET_H
