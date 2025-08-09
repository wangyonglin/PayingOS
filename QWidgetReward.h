#ifndef QWIDGETREWARD_H
#define QWIDGETREWARD_H

#include <QWidget>

class QWidgetReward : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetReward(QWidget *parent = nullptr);

public slots:
    void setTitle(const QString &name);
signals:
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString qstringTitleName;
};

#endif // QWIDGETREWARD_H
