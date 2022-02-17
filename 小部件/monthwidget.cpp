#include "monthwidget.h"
#include "yearwidget.h"
#include <QLabel>
#include <QPalette>
#include <QDebug>
#include <QFont>

#define dx 146
#define dy 70
#define w 120
#define h 54

MonthWidget::MonthWidget(QWidget *parent, int year) : QWidget(parent)
{
    this->setFixedSize(586, 302);
    QPalette  whitePe;//设置字体颜色 白色
    whitePe.setColor(QPalette::WindowText,Qt::white);
    QFont f("Microsoft YaHei", 12, 70);//设置字体、字号 微软雅黑 8号

    labelYear = new QLabel(this);//////年份标签初始化
    labelYear->move(490, 17);
    labelYear->setPalette(whitePe);
    labelYear->setText(QString::number(year++)+"年");
    labelYear->setFont(QFont("Microsoft YaHei", 12));//设置文本字体、字号

    //////月份标签初始化
    for(int index = 0; index < 12; index++)
    {
        qlabel_group.push_back(new QLabel(this));
        qlabel_group[index]->setText(QString::number(index+1) + "月");
        qlabel_group[index]->move( 13 + dx * (index % 4), 56 + dy * (index / 4));//x轴 y轴
        qlabel_group[index]->setPalette(whitePe);//设置文本颜色
        qlabel_group[index]->setFont(f);//设置文本字体、字号
        qlabel_group[index]->setFixedSize(w, h);//在使用QLable的setAlignment的时候，必须设置size
        qlabel_group[index]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置文字对齐方式  水平居中 垂直居中
    }

    selectedIndex = 0;
}

int MonthWidget::getYear()
{
    return year;
}

void MonthWidget::setYear(int year)
{
    labelYear->setText(QString::number(year) + "年");
    qDebug()<<"设置月历中的年份标签";
    this->year = year;
}

//重写鼠标点击事件
void MonthWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug()<<"按下鼠标";
        int x = event->x() % dx;
        int y = event->y()-56;
        if( x>13 && x<133 && y>0)
        {
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
            selectedIndex = ((event->y()-56) / dy) * 4 + (event->x()/dx);
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url(:/res/whiteBorder.png)");
        }
    }
}

//重写鼠标双击事件
void MonthWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug()<<"按下鼠标";
        int x = event->x() % dx;
        int y = event->y()-56;
        if( x>13 && x<133 && y>0)
        {
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
            selectedIndex = ((event->y()-56) / dy) * 4 + (event->x()/dx);
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url(:/res/whiteBorder.png)");
            int m = selectedIndex + 1;//由于selectedIndex是索引号 故需要再+1
            emit this->monthChoosed( m );//发出已有年份被双击选中的信号
        }
        qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");//取消选择
    }
}

//槽函数  当年历双击选中年份后，月历右上角的年份标签也要随之更改
void MonthWidget::changeYear(int year)
{
    qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");//之前选中的标签要取消选择

    labelYear->setText(QString::number(year) + "年");
    qDebug()<<"重设月历中的年份标签";
    this->year = year;
}
