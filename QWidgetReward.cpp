#include "QWidgetReward.h"
#include <QPainter>
QWidgetReward::QWidgetReward(QWidget *parent)
    : QWidget{parent}
{
    setStyleSheet("background: #FF9999;"); // 示例样式
    setTitle("QWidgetReward");
}

void QWidgetReward::setTitle(const QString &name)
{
    qstringTitleName=name;
    update();
}

void QWidgetReward::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage canvas(size(), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);

    //标题
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    QFontMetrics titleFontMetrics(painter.font());
    painter.drawText(canvas.width()/2 - titleFontMetrics.horizontalAdvance(qstringTitleName)/2,
                     canvas.height()/12, qstringTitleName);

}
