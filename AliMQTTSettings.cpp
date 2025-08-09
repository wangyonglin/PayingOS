#include "AliMQTTSettings.h"
#include <QDebug>
#include <QMessageAuthenticationCode>
#include <QCryptographicHash>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QRegularExpression>


AliMQTTSettings::AliMQTTSettings(const QString &filename,QObject *parent)
    :QSettings{filename,IniFormat,parent}{
    productKey= value("alimqtt/productKey","").toString();
    qDebug() << "productKey:" << productKey;
    deviceName= value("alimqtt/deviceName","").toString();
    deviceSecret= value("alimqtt/deviceSecret","").toString();
    hostUrl=value("alimqtt/hostUrl","").toString();
    port=value("alimqtt/port","1883").toString().toInt();
}

QString AliMQTTSettings::getDeviceName(){
    /* setup deviceName */
    return deviceName;
}
QString AliMQTTSettings::getProductKey(){
    /* setup productKey */
    return productKey;
}
QString AliMQTTSettings::getDeviceSecret(){
    /* setup deviceSecret */
    return deviceSecret;
}




QString AliMQTTSettings::getDeviceID(){
    /* setup deviceid */
    if(!getProductKey().isEmpty() && !getDeviceName().isEmpty()){
        return QString("%1.%2").arg(getProductKey()).arg(getDeviceName());
    }
    return nullptr;
}
QString AliMQTTSettings::getClientID(){
    /* setup clientid */
    if(!getProductKey().isEmpty() && !getDeviceName().isEmpty() && TIMESTAMP_VALUE){
        return QString("%1|securemode=2,signmethod=hmacsha256,timestamp=%2|").arg(getDeviceID()).arg(TIMESTAMP_VALUE);
    }
    return nullptr;
}

QString AliMQTTSettings::getUsername(){

    if(!getDeviceName().isEmpty() && !getProductKey().isEmpty()){
        return QString("%1&%2").arg(getDeviceName()).arg(getProductKey());
    }
    return nullptr;
}

QString AliMQTTSettings::getPassword(){
    /* setup password */
    QString mac;
    mac.append(QString("clientId%1.%2").arg(getProductKey()).arg(getDeviceName()));
    mac.append(QString("deviceName%1").arg(getDeviceName()));
    mac.append(QString("productKey%1").arg(getProductKey()));
    mac.append(QString("timestamp%1").arg(TIMESTAMP_VALUE));
    qDebug() << mac;
    return hmacSha256(getDeviceSecret().toUtf8(),mac.toUtf8());
}
QString AliMQTTSettings::getHostUrl(){
    if(!hostUrl.isEmpty()){
        return QString("%1.%2").arg(getProductKey()).arg(hostUrl);
    }
    return nullptr;
}

QString AliMQTTSettings::getTopic(const QString &topic)
{
  return QString("%1/%2%3").arg(getProductKey()).arg(getDeviceName()).arg(topic);
}

quint16 AliMQTTSettings::getPort(){
    return port;
}

QString AliMQTTSettings::encryptPassword(const QString &password)
{
    QByteArray passwordData = password.toUtf8();
    // 使用SHA256算法进行哈希计算
    QByteArray hash = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
QCryptographicHashPrivate:
    // 转换为十六进制字符串表示，这里不再截取，保留完整的哈希结果
    return QString(hash.toHex());
}
QString AliMQTTSettings::hmacSha256(const QByteArray &key, const QByteArray &data) {
    QByteArray hash= QMessageAuthenticationCode::hash(data, key, QCryptographicHash::Sha256);
    // 转换为十六进制字符串表示，这里不再截取，保留完整的哈希结果
    return QString(hash.toHex());
}

