#include "QWidgetManager.h"

QWidgetManager::QWidgetManager(QWidget *parent)
    : QStackedWidget{parent}
{
    setStyleSheet("QStackedWidget { background-color: #FF0000; }");

    aliMQTTSettings= new AliMQTTSettings("/home/wangyonglin/conf/loongc.conf",this);
    aliMQTTClient= new AliMQTTClient(this);

    aliMQTTClient->addTopic(aliMQTTSettings->getTopic("/user/get"));
    qWidgetPayment= new QWidgetPayment(this);
    qWidgetReward= new QWidgetReward(this);
    addWidget(qWidgetPayment);
    addWidget(qWidgetReward);
    setCurrentWidget(qWidgetPayment);

    aliMQTTClient->setHostname(aliMQTTSettings->getHostUrl());
    aliMQTTClient->setPort(aliMQTTSettings->getPort());
    aliMQTTClient->setClientId(aliMQTTSettings->getClientID());
    aliMQTTClient->setPassword(aliMQTTSettings->getPassword());
    aliMQTTClient->setUsername(aliMQTTSettings->getUsername());
    aliMQTTClient->connectToHost();
}

QWidgetManager::~QWidgetManager()
{
    aliMQTTClient->disconnectFromHost();
}

void QWidgetManager::resizeEvent(QResizeEvent *event)
{
    qWidgetPayment->resize(event->size());
    qWidgetReward->resize(event->size());
}

void QWidgetManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1){
        qWidgetPayment->setTitle("qWidgetPayment");
        setCurrentWidget(qWidgetPayment);
    }else if(event->key() == Qt::Key_F2){
         qWidgetReward->setTitle("qWidgetReward");
        setCurrentWidget(qWidgetReward);
    }
}
