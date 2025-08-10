#include "QWidgetManager.h"

QWidgetManager::QWidgetManager(QWidget *parent)
    : QStackedWidget{parent}
{
    qDebug() << Qt6Identify::build();
    setStyleSheet("QStackedWidget { background-color: #CCCCCC; }");

    allSettings= new AllSettings("/home/wangyonglin/conf/loongc.conf",this);

    aliMQTTClient= new AliMQTTClient(this);
    //链接断开时进行重连
    connect(aliMQTTClient, &QMqttClient::disconnected, this, [this](){
        setStyleSheet("QStackedWidget { background-color: #CCCCCC; }");
    });
    //链接成功时进行订阅
    connect(aliMQTTClient, &QMqttClient::connected, this, [this](){
        setStyleSheet("QStackedWidget { background-color: #FF0000; }");
    });

    aliMQTTClient->addTopic(allSettings->getTopic("/user/get"));
    qWidgetPayment= new QWidgetPayment(this);
    qWidgetReward= new QWidgetReward(this);
    addWidget(qWidgetPayment);
    addWidget(qWidgetReward);
    setCurrentWidget(qWidgetReward);

    aliMQTTClient->setHostname(allSettings->getHostUrl());
    aliMQTTClient->setPort(allSettings->getPort());
    aliMQTTClient->setClientId(allSettings->getClientID());
    aliMQTTClient->setPassword(allSettings->getPassword());
    aliMQTTClient->setUsername(allSettings->getUsername());
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
        qWidgetPayment->setTitle("--- 扫码支付 ---");
        setCurrentWidget(qWidgetPayment);
    }else if(event->key() == Qt::Key_F2){
        qWidgetReward->setTitle("qWidgetReward");
        setCurrentWidget(qWidgetReward);
    }else if(event->key() == Qt::Key_F3){

    }
    qWidgetPayment->keyPressEvent(event);
}
