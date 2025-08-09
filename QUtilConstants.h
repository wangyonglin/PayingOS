#ifndef QUTILCONSTANTS_H
#define QUTILCONSTANTS_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class QUtilConstants : public QObject
{
    Q_OBJECT
public:
    explicit QUtilConstants(QObject *parent = nullptr);

    static QString getBiosSerial();
    static QString getCpuId();
    static QString getDiskSerial();
    static QString getDeviceId();

signals:
};

#endif // QUTILCONSTANTS_H
