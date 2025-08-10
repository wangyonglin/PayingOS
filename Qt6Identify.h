#ifndef QT6IDENTIFY_H
#define QT6IDENTIFY_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class Qt6Identify : public QObject
{
    Q_OBJECT
public:
    explicit Qt6Identify(QObject *parent = nullptr);
    static QString build();
private:
    static QString getMACIdentify();
    static QString getCPUIdentify();
};

#endif // QT6IDENTIFY_H
