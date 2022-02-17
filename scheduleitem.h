#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QTextEdit>
#include "star.h"

namespace Ui {
class ScheduleItem;
}

class ScheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleItem(QWidget *parent = 0);
    ~ScheduleItem();

//    bool eventFilter(QObject *watched, QEvent *event);//事件过滤器
    void leaveEvent(QEvent *event);//重写鼠标离开事件

private:
    Ui::ScheduleItem *ui;
};

#endif // SCHEDULEITEM_H
