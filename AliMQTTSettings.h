#ifndef ALIMQTTSETTINGS_H
#define ALIMQTTSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QByteArray>
#include <QMessageAuthenticationCode>
#include <QCryptographicHash>
#include <QString>
#include "QUtilConstants.h"

#define TIMESTAMP_VALUE             "1754671526672"
#define MQTT_CLINETID_KV            "|securemode=2,signmethod=hmacsha256,timestamp=1754671526672|"
class AliMQTTSettings : public QSettings
{
    Q_OBJECT
public:
    explicit AliMQTTSettings(const QString & filename="../conf/loongc.conf",QObject *parent = nullptr);
    QString getDeviceID();
    QString getClientID();
    QString getUsername();
    QString getDeviceName();
    QString getProductKey();
    QString getDeviceSecret();
    QString getPassword();
    QString getHostUrl();
    quint16 getPort();
    QString getTopic(const QString &topic);
private:
    QString productKey;
    QString deviceName;
    QString deviceSecret;
    QString hostUrl;
    quint16 port=1883;
    QString encryptPassword(const QString &password);
    QString hmacSha256(const QByteArray &key, const QByteArray &data);
};

#endif // ALIMQTTSETTINGS_H
