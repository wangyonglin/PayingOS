#ifndef QWIDGETMANAGER_H
#define QWIDGETMANAGER_H

#include <QWidget>
#include <QStackedWidget>
#include "QWidgetPayment.h"
#include "QWidgetReward.h"
#include "AliMQTTClient.h"
#include "AliMQTTSettings.h"

class QWidgetManager : public QStackedWidget
{
    Q_OBJECT
public:
    explicit QWidgetManager(QWidget *parent = nullptr);
    ~QWidgetManager();
private:
    QStackedWidget *stackedWidget;
    QWidgetPayment *qWidgetPayment;
    QWidgetReward *qWidgetReward;
    AliMQTTClient *aliMQTTClient;
    AliMQTTSettings * aliMQTTSettings;
signals:

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // QWIDGETMANAGER_H
