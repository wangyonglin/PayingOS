#ifndef QPaymentWidgetBACK_H
#define QPaymentWidgetBACK_H
#include <QWidget>
#include <QKeyEvent>
#include "QPaymentObject.h"

class QPaymentWidget : public QPaymentObject
{
    Q_OBJECT

public:
    QPaymentWidget(QWidget *parent = nullptr);
    ~QPaymentWidget();

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
#endif // QPaymentWidgetBACK_H
