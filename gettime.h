#ifndef GETTIME_H
#define GETTIME_H

#include <QObject>
#include <QTimer>
#include <time.h>
#include <stdio.h>
#include <QVector>
#include <QMap>
#include "lunarcalendar.h"

class GetTime : public QObject
{
    Q_OBJECT
public:
    explicit GetTime(QObject *parent = nullptr);

    QString getHMS();//获取时分秒  字符串
    QString getYMD();//获取某年某月某日  字符串

    int getYear() const;//获取年份
    int getMonth() const;//获取月份
    int getToday() const;//获取今天
    int getTodayIndex() const;//获取今日所在的索引号

    void setData(int month, int year = 0);//设置月份，年份
    int getM() const;
    int getY() const;

    //属性 月份数组  6行7列
    int monthDayArray[42] ;//记录日
    bool monthBoolArray[42];//判断此日是否属于当月 是则为1 否则为0
    QString monthLunarArray[42];//记录农历、节日
    //方法 设置月数组
    void setMonthArray();

private:
    time_t systermTime = time(NULL);    //系统时间
    int year,month,today,todayIndex;  //当下的年份  月份 天数（不可修改）
    int y,m;//找寻页的 年份 月份（可修改）
    bool leapYear;

    int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//用数组保存每个月的天数
    int daysCommonYear[12] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};//用数组保存一般年  每个月的第一天  是全年的第几天

    bool isLeapYear(int year);//方法 判断是否是闰年

    int getBfDay(int today);    //方法 获取昨天的日期
    int getAfDay(int today);    //方法 获取明天的日期

    int charTransformInt(char * a);//方法 字符数组char*转数字int

    LunarCalendar *l;

signals:

public slots:
    //槽函数 接收由月历发来的被选中月份、被选中年份的信息，设置年份、月份，从而设置找寻月的月数组，更新thatWidget
    void setM(int month);//设置月份
    void setY(int year);//设置年份
};

#endif // GETTIME_H
