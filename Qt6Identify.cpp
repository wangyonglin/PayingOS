#include "Qt6Identify.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QMessageAuthenticationCode>
#include <QProcess>
#include <cpuid.h>
#include <sstream>
// 获取BIOS序列号 (Linux系统)
Qt6Identify::Qt6Identify(QObject *parent)
    :QObject{parent}
{

}
// 获取硬盘序列号（备用）
QString Qt6Identify::getMACIdentify() {
    foreach (const QNetworkInterface &net, QNetworkInterface::allInterfaces()) {
        if (!(net.flags() & QNetworkInterface::IsLoopBack) &&
            !net.hardwareAddress().isEmpty() &&
            net.hardwareAddress() != "00:00:00:00:00:00") {
            return net.hardwareAddress().remove(':');
        }
    }
    return QString("00:00:00:00:00:00").remove(':');
}

QString Qt6Identify::getCPUIdentify()
{
    unsigned int level = 1;
    unsigned eax = 3 /* processor serial number */, ebx = 0, ecx = 0, edx = 0;
    __get_cpuid(level, &eax, &ebx, &ecx, &edx);

    // byte swap
    int first = ((eax >> 24) & 0xff) | ((eax << 8) & 0xff0000) | ((eax >> 8) & 0xff00) | ((eax << 24) & 0xff000000);
    int last = ((edx >> 24) & 0xff) | ((edx << 8) & 0xff0000) | ((edx >> 8) & 0xff00) | ((edx << 24) & 0xff000000);

    // tranfer to string
    QByteArray byts;
    QDataStream stream(&byts, QIODevice::WriteOnly);
    stream << first;
    stream << last;
    return byts.toHex().toUpper();
}

QString Qt6Identify::build()
{
    QString cpu =getCPUIdentify();
    QString max = getMACIdentify();
    if(!cpu.isEmpty() && max.isEmpty()){
        // 组合硬件信息
        QString cpumaxIdentify = QString("%1|%2")
                                   .arg(cpu)
                                   .arg(max);

        // 生成更安全的哈希 (SHA256比SHA1更推荐)
        QByteArray hash = QCryptographicHash::hash(
            cpumaxIdentify.toUtf8(),
            QCryptographicHash::Md5
            );

        return hash.toHex().toUpper();
    }
    QByteArray hash = QCryptographicHash::hash(
        QString("").toUtf8(),
        QCryptographicHash::Md5
        );

    return hash.toHex().toUpper();
}
