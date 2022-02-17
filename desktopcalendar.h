#ifndef DESKTOPCALENDAR_H
#define DESKTOPCALENDAR_H

#include <QWidget>
#include <QPoint>
#include <QStringList>

//////////自定义控件//////
#include "mypushbutton.h"
#include "star.h"  //闪烁的星星
#include "widgets/daywidget.h"
#include "widgets/monthwidget.h"
#include "widgets/yearwidget.h"
#include "gettime.h"
#include "scheduleitem.h"
#include "scheduleedit.h"

namespace Ui {
class DesktopCalendar;
}

class DesktopCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit DesktopCalendar(QWidget *parent = 0);
    ~DesktopCalendar();

    void paintEvent(QPaintEvent *event);    //绘制背景图

    void buttonInfo();//初始化按钮
    void mini();//最小化到托盘

    void mousePressEvent(QMouseEvent * event);//重写鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);//重写鼠标移动事件
    //void mouseReleaseEvent(QMouseEvent *event);//重写鼠标释放事件
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);//重写关闭

private:
    Ui::DesktopCalendar *ui;
    GetTime * gt;
    dayWidget *thisDaysWidget;
    MonthWidget *monthWidget;
    YearWidget *yearWidget;
    dayWidget *thatDaysWidget;
    ScheduleEdit *edit;

    QStringList calendar;  //字符串链表  记录日程
    int beforeIndex;

    QPoint clickPos;   //鼠标拖动的位置

    //展示时分秒
    void HMS_show();

};

#endif // DESKTOPCALENDAR_H
