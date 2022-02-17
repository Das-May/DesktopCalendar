#include "gettime.h"
#include "lunarcalendar.h"
#include <QDebug>
#include <QStringList>


GetTime::GetTime(QObject *parent) : QObject(parent)
{
    //初始化 年月日 int属性
    char str[5];
    strftime( str, sizeof(str), "%Y",localtime(&systermTime) );
    year = charTransformInt(str);
    strftime( str, sizeof(str), "%m",localtime(&systermTime) );
    month = charTransformInt(str);
    strftime( str, sizeof(str), "%d",localtime(&systermTime) );
    today = charTransformInt(str);

    y = year;
    m = month;
    leapYear = isLeapYear(y);

    l = new LunarCalendar(this);

    //初始化 当月数组
    setMonthArray();

}

//判断是否是闰年
bool GetTime::isLeapYear(int year)
{
    if(year % 4 == 0 && year % 100 != 0)
        return true;
    else
        return false;
}

//获取时分秒
QString GetTime::getHMS()
{
    char str[32];
    strftime( str, sizeof(str), "%H:%M:%S",localtime(&systermTime) );
    return QString(str);
}

//获取年月日  附带阴历年
QString GetTime::getYMD()
{
    char str[32];
    strftime( str, sizeof(str), " %Y年%m月%d日 ",localtime(&systermTime) );
    QString s = QString(str) + " " + l->getLunarMonthDay(year,month,today) ;
    return s;
}

//获取年份
int GetTime::getYear() const
{
    return year;
}

//获取月份
int GetTime::getMonth() const
{
    return month;
}

//获取今天
int GetTime::getToday() const
{
    return today;
}
//获取今天的索引号
int GetTime::getTodayIndex() const
{
    return todayIndex;
}

//设置月份，年份
void GetTime::setData(int month, int year)
{
    if(year == 0) year = this->y;
    if(month > 12)
    {
        year++;
        month = 1;
    }
    else if(month < 1)
    {
        year--;
        month = 12;
    }
    this->m = month;
    this->y = year;
    qDebug()<<this->y<<"年"<<this->m<<"月";
}


int GetTime::getM() const
{
    return m;
}
int GetTime::getY() const
{
    return y;
}

//方法 初始化月数组
void GetTime::setMonthArray()
{
    ////////设置当月第一天天数戳/////
    int dayStamp = (y-1970)*365 + daysCommonYear[m-1] + (y-1972)/4 - 1;//此天数戳为所找寻的某年某月的第一天的天数戳
    if(y > 2000)
        dayStamp+=(y-2000)/400 + 1;
    if(isLeapYear(y) && m < 2) dayStamp--;

    ///////获取本月第一天的索引号/////
    //以1970年1月1日(星期四)为日历的第0行第4列(数组索引号)  每42天为一格
    //那么本月的第一天就是第((3 + dayStamp%42%7)/7)行,第((3 + dayStamp%42%7)%7)列
    //为了保证每月的第1天在第1行 则当前时间的位置是：
    //第1+(today/7)行 第((thisTimeStamp/60/60/24%42)%7)列 索引号为 3+thisTimeStamp/60/60/24%42%7 + (day/7)*7
    int index = 3 + dayStamp%42%7 ; //本月第一天的索引号
    qDebug()<<"本月第一天的索引号："<<index;
    todayIndex = index + today - 1; /*其实这个初始化只用一次 后续再次调用其实是无用功*/
    qDebug()<<"今天的索引号："<<todayIndex;
    int d;//d 天数

    ///////设置上个月的数组//////
    setData(m - 1);
    d = 1;
    for(int i = index - 1; i > -1; i--)//从上个月的最后一天开始
    {
        d = getBfDay ( d );
        monthBoolArray[i] = false; //将上个月的Bool数组置为0  即字体设为灰色
        monthDayArray[i] = d;
        qDebug()<<monthDayArray[i];
        monthLunarArray[i] = l->getLunarInfo(y, m, d, 0, 0, 1);
    }


    ////////设置本月数组//////
    setData(m + 1);
    d = 1;
    for(int i = index; ; i++)//从本月的第一天开始
    {
        monthBoolArray[i] = true; //将本月的Bool数组置为1  即字体设为白色
        monthDayArray[i] = d;
        monthLunarArray[i] = l->getLunarInfo(y, m, d, 0, 0, 1);
        //qDebug()<<monthLunarArray[i];
        d = getAfDay ( d );
        if(d == 1) {
            index = i+1;//设置索引号为下个月的第一天
            break;
        }
    }

    ///////设置下个月的数组///////
    setData(m + 1);
    for(int i = index; i < 42; i++)//从下个月的第一天开始
    {
        monthBoolArray[i] = false; //将下个月的Bool数组置为0  即字体设为灰色
        monthDayArray[i] = d;
        monthLunarArray[i] = l->getLunarInfo(y, m, d, 0, 0, 1);
        d = getAfDay ( d );
    }

    /////还原m//////
    setData(m - 1);

}

//方法 获取昨天的日期
int GetTime::getBfDay(int today)
{
    int bfDay;
    if(today > 1){
        bfDay = --today;//大量运算时，要尤其注意--i和i--的区别
    }
    else{
        if(leapYear && m==3)
            bfDay = 29;
        else
        {
            bfDay = days[ m - 1 ];//索引号需要-1
        }
    }
    return bfDay;
}

//方法 获取明天的日期
int GetTime::getAfDay(int today)
{
    int afDay;
    if(leapYear && m==2 && today==28)
        afDay = 29;
    else if(today < days[m - 1])
        afDay = ++today;
    else
    {
        afDay = 1;
    }
    return afDay;
}

//方法 字符数组char*转数字int
int GetTime::charTransformInt(char * a)
{
    int num = 0;
    int i = 0;
    while(a[i]!='\0')
    {
        num = num*10 + a[i]-48;
        i++;
    }
    return num;
}

//槽函数 设置月份
void GetTime::setM(int month)
{
    setData(month);
    qDebug()<<"设置月份"<<month;
}

//槽函数 设置年份
void GetTime::setY(int year)
{
    qDebug()<<"设置年份"<<year;
    this->y = year;
    leapYear = isLeapYear(year);
}
