#ifndef DAYSWIDGET_H
#define DAYSWIDGET_H

#include <QWidget>
#include <QLabel>
#include "gettime.h"
#include "scheduleitem.h"

class dayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit dayWidget(QWidget *parent = nullptr, GetTime *gt = new GetTime);

    int getSeletedDay();//获取被选中的label的天数
    void update(GetTime *gt);//更新日历
    bool addSchedule();//添加事件
    bool deleteSchedule();//删除事件
    void mousePressEvent(QMouseEvent *event);    //重写鼠标点击事件

private:
    QString weekday[7]={"一","二","三","四","五","六","日"};
    QVector<QLabel*> qlabel_group; //维护日历QLabel数组
    bool tags[42];
    int todayIndex;//今天所在的label的索引号
    int selectedIndex;//被选中的label的索引号
    bool tag;//判断是否作为当前月份的日历 若是，则1 若否，则0
    QVector<ScheduleItem*> s;

signals:

public slots:

};

#endif // DAYSWIDGET_H
