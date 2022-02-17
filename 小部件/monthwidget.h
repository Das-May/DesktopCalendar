#ifndef MONTHWIDGET_H
#define MONTHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include "gettime.h"
#include "yearwidget.h"
#include <QObject>
#include <QEvent>

class MonthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonthWidget(QWidget *parent = nullptr, int year = 2021);

    int getYear();//获取年份
    void setYear(int year);//设置年份

    void mousePressEvent(QMouseEvent *event);    //重写鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);    //重写鼠标双击事件

private:
    int year;//记录年份
    int selectedIndex;//记录被选中的月份的索引号

    QLabel *labelYear;//展示年份的标签
    QVector<QLabel*> qlabel_group; //月份QLabel数组


signals:
    void monthChoosed(int month);//信号 已有月份被双击选中

public slots:
    //槽函数  当年历双击选中年份后，月历右上角的年份标签也要随之更改
    void changeYear(int year);

};

#endif // MONTHWIDGET_H
