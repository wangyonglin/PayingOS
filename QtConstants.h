#ifndef QTCONSTANTS_H
#define QTCONSTANTS_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class QtConstants : public QObject
{
    Q_OBJECT
public:
    explicit QtConstants(QObject *parent = nullptr);

    static QString getBiosSerial();
    static QString getCpuId();
    static QString getDiskSerial();
    static QString getDeviceId();

signals:
};

#endif // QTCONSTANTS_H
