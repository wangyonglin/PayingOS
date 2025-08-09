#ifndef ALIMQTTCLIENT_H
#define ALIMQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QTimer>
#include "AliMQTTSettings.h"
class AliMQTTClient : public QMqttClient
{
    Q_OBJECT
public:
    explicit AliMQTTClient(QObject *parent = nullptr);
    ~AliMQTTClient();
    void connectToHost();
    void disconnectFromHost();
    //设置最大延迟链接时间
    void setReconnectMaxDelayTime(int i){m_maxDelay = i;}
    //发送消息
    void publishMessage(const QString &message, const QString &topic);
    //增加订阅
    void addTopic(const QString &topic);
    //移除订阅
    void removeTopic(const QString &topic);
signals:
    void connectState(bool state);
public slots:
    void subscribeAll();
private:
    QTimer *_timer = new QTimer(this);
    //最大延迟连接时间
    int m_maxDelay = 900000;
    int m_time = 1000;
    QStringList m_topics;
};

#endif // ALIMQTTCLIENT_H
