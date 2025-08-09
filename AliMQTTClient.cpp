#include "AliMQTTClient.h"


AliMQTTClient::AliMQTTClient(QObject *parent)
    : QMqttClient{parent}
{
    //链接断开时进行重连
    connect(this, &QMqttClient::disconnected, this, [this](){
        _timer->start(m_time);
    });
    //链接成功时进行订阅
    connect(this, &QMqttClient::connected, this, [this](){
        subscribeAll();
    });
    //有消息时进行消费
    connect(this, &QMqttClient::messageReceived, this, [](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" Received Topic: ")
            + topic.name()
            + QLatin1String(" Message: ")
            + message
            + QLatin1Char('\n');
        qDebug() << content;
    });

    //触发重新计时器
    connect(_timer, &QTimer::timeout, this, [this](){
        //重新链接
        connectToHost();
        //如果延迟时间小于最大延迟时间则加15秒
        if(m_time < m_maxDelay){
            m_time = m_time + 15000;
        }
        qDebug() << QString("reconnect times: %1").arg((m_time - 1000) / 15000);
        //一定要停止当前的计时器
        _timer->stop();
    });

}

AliMQTTClient::~AliMQTTClient()
{
    disconnectFromHost();
}

void AliMQTTClient::connectToHost()
{
    if(state()==QMqttClient::Disconnected){
        QMqttClient::connectToHost();
    }
}

void AliMQTTClient::disconnectFromHost()
{
    if(state()==QMqttClient::Connected){
        QMqttClient::disconnectFromHost();
    }
}
void AliMQTTClient::publishMessage(const QString &message, const QString &topic)
{
    if(state() == QMqttClient::Connected){
        qint32 localPublish = publish(topic, message.toUtf8());
        if(localPublish < 0){
            qDebug() << QString("send message : %1 to topic: %2 faild.").arg(message).arg(topic);
        }
    }
}

void AliMQTTClient::addTopic(const QString &value)
{
    if(value.isEmpty())return;
    if(!m_topics.contains(value)){
        m_topics << value;
        QMqttSubscription *localSubscribe = subscribe(value);
        if(!localSubscribe){
            qDebug() << QString("subscribe topic : %1 faild.").arg(value);
        }
        else{
            qDebug() << QString("subscribe topic : %1 succes.").arg(value);
        }
    }
}

void AliMQTTClient::removeTopic(const QString &topic)
{
    unsubscribe(topic);
    m_topics.removeOne(topic);
}

void AliMQTTClient::subscribeAll()
{
    //链接成功后停止计时器，重置重连延迟时间，订阅主题
    _timer->stop();
    m_time = 1000;
    for(QString topic : m_topics){
        QMqttSubscription *localSubscribe = subscribe(topic);
        if(!localSubscribe){
            qDebug() << QString("subscribe topic : %1 faild.").arg(topic);
        }
        else{
            qDebug() << QString("subscribe topic : %1 succes.").arg(topic);
        }
    }
}
