#include "QUtilConstants.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QMessageAuthenticationCode>


// 获取BIOS序列号 (Linux系统)
QUtilConstants::QUtilConstants(QObject *parent)
    :QObject{parent}
{

}


QString QUtilConstants::getBiosSerial() {
    QFile file("/sys/class/dmi/id/product_serial");
    if (file.open(QIODevice::ReadOnly)) {
        return QString::fromLatin1(file.readAll()).trimmed();
    }
    return "UNKNOWN_BIOS";
}

// 获取CPU ID (Linux系统)
QString QUtilConstants::getCpuId() {
    QFile file("/proc/cpuinfo");
    if (file.open(QIODevice::ReadOnly)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            if (line.startsWith("Serial")) {
                return line.split(':').last().trimmed();
            }
        }
    }
    return "UNKNOWN_CPU";
}

// 获取磁盘序列号 (跨平台)
QString QUtilConstants::getDiskSerial() {
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady() && !storage.isReadOnly()) {
// 在Linux上获取实际设备标识
#ifdef Q_OS_LINUX
            QFile devFile(storage.device());
            if (devFile.open(QIODevice::ReadOnly)) {
                QByteArray devId = devFile.readAll();
                if (!devId.isEmpty()) {
                    return QCryptographicHash::hash(devId, QCryptographicHash::Md5).toHex();
                }
            }
#endif

            // 通用回退方案
            return storage.device() + storage.fileSystemType();
        }
    }
    return "UNKNOWN_DISK";
}

// 生成增强版设备ID
QString QUtilConstants::getDeviceId() {
    // 获取硬件信息
    QString biosSerial = getBiosSerial();
    QString cpuId = getCpuId();
    QString diskSerial = getDiskSerial();

    // 添加MAC地址增强唯一性
    QString macAddress = "NO_MAC";
    foreach (const QNetworkInterface &net, QNetworkInterface::allInterfaces()) {
        if (!(net.flags() & QNetworkInterface::IsLoopBack) &&
            !net.hardwareAddress().isEmpty() &&
            net.hardwareAddress() != "00:00:00:00:00:00") {
            macAddress = net.hardwareAddress().remove(':');
            break;
        }
    }

    // 组合硬件信息
    QString hardwareInfo = QString("%1|%2|%3|%4")
                               .arg(biosSerial)
                               .arg(cpuId)
                               .arg(diskSerial)
                               .arg(macAddress);

    // 生成更安全的哈希 (SHA256比SHA1更推荐)
    QByteArray hash = QCryptographicHash::hash(
        hardwareInfo.toUtf8(),
        QCryptographicHash::Md5
        );

    return hash.toHex().toUpper();
}


