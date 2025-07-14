#ifndef PAYINGWIDGET_H
#define PAYINGWIDGET_H

#include <QWidget>
#include "QRcodePainter.h"

class PayingWidget : public QWidget
{
    Q_OBJECT

public:
    PayingWidget(QWidget *parent = nullptr);
    ~PayingWidget();

private:
   // QRcodePainter *rcode;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;


    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};
#endif // PAYINGWIDGET_H
