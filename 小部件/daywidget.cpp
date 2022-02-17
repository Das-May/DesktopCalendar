#include "daywidget.h"
#include <QPalette>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QFont>



#define DX 78
#define DY 42
#define W 52
#define H 38


dayWidget::dayWidget(QWidget *parent, GetTime *gt) : QWidget(parent)
{
    tag = 1;
    selectedIndex = -1;//无label被选中时 初始化为-1

    QPalette  whitePe;//设置字体颜色 白色
    whitePe.setColor(QPalette::WindowText,Qt::white);
    QPalette  grayPe;//设置字体颜色 灰色
    grayPe.setColor(QPalette::WindowText,Qt::gray);
    QFont f("Microsoft YaHei", 8, 70);//设置字体、字号、字重 ：微软雅黑 8号 加粗

    ////////表头//////
    for(int i = 0 ;i < 7 ;i++)
    {
        QLabel *label = new QLabel(this);
        label->setText(weekday[i]);
        label->setPalette(whitePe);
        label->move(15 + DX * i, 0);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFixedSize(W, H);//在使用QLable的setAlignment的时候，必须设置size
        label->setFont(f);//设置文本字体、字号
    }

    ////////日期 + 记事的星星/////////
    for(int i = 0 ;i < 42; i++)
    {

        qlabel_group.push_back(new QLabel(this));
        qlabel_group[i]->setAlignment(Qt::AlignHCenter | Qt::AlignTop);//设置对齐方式
        QString text;
        text.append("<p style='line-height:20%'>").append(QString::number(gt->monthDayArray[i])).
                append("</p>").append("<p style='line-height:10%'>").append(gt->monthLunarArray[i]).append("</p>");
        qlabel_group[i]->setText(text);

        if(gt->monthBoolArray[i] == true)//设置文本颜色
            qlabel_group[i]->setPalette(whitePe);
        else
            qlabel_group[i]->setPalette(grayPe);
        tags[i] = gt->monthBoolArray[i];

        qlabel_group[i]->setFont(f);//设置文本字体、字号
        //move的第一个参数是x轴坐标 对应第几列
        //第二个参数时y轴坐标，对应第几行
        qlabel_group[i]->move(15 + DX * (i % 7), 45 + DY*(i / 7));//设置位置
        qlabel_group[i]->setFixedSize(W, H);//在使用QLable的setAlignment的时候，必须设置size

        s.push_back(new ScheduleItem(this));
        s[i]->move(DX * (i % 7) + 46, DY*(i / 7) + 28);
        s[i]->raise();
        s[i]->hide();
        //在别的widget中，自定义的widget是默认显示的
        //在主窗口中，自定义的widget是默认隐藏的
    }

    todayIndex = gt->getTodayIndex();
    if(gt->getM() == gt->getMonth())
    {
        qlabel_group[todayIndex]->setStyleSheet("border-image: url(:/res/stressBackground.png);color:black;");//对于今天的日期，要尤其强调
    }
}
//获取被选中的label的天数
int dayWidget::getSeletedDay()
{
    QString t = qlabel_group[selectedIndex]->text().mid(27, 2);
    qDebug() << t;
    if(t.toInt() != 0)
    {
        qDebug() << t;
        qDebug() << t.toInt();
        return t.toInt();
    }
    else
    {
        t = t.left(1);
    }
    qDebug() << t;
    qDebug() << t.toInt();
    return t.toInt();
}

//更新日历
void dayWidget::update(GetTime *gt)
{
    tag = 0;//tag==0说明这是其它月的日历了，则原来强调的“当天的label”就不需要强调了
    qlabel_group[todayIndex]->setStyleSheet("border-image: url();");
    if(selectedIndex != -1)
        qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
    selectedIndex = -1;

    QPalette  whitePe;//设置字体颜色 白色
    whitePe.setColor(QPalette::WindowText,Qt::white);
    QPalette  grayPe;//设置字体颜色 灰色
    grayPe.setColor(QPalette::WindowText,Qt::gray);

    for(int i = 0 ;i < 42;i++)
    {
        QString text;
        text.append("<p style='line-height:20%'>").append(QString::number(gt->monthDayArray[i])).
                append("</p>").append("<p style='line-height:10%'>").append(gt->monthLunarArray[i]).append("</p>");
        qlabel_group[i]->setText(text);
        if(gt->monthBoolArray[i] == true)//设置文本颜色
            qlabel_group[i]->setPalette(whitePe);
        else
            qlabel_group[i]->setPalette(grayPe);
        tags[i] = gt->monthBoolArray[i];
    }
}

//添加事件
bool dayWidget::addSchedule()
{
    if(selectedIndex == -1 || tags[selectedIndex] == false) {return false;}
    s[selectedIndex]->show();
    return true;
}

//删除事件
bool dayWidget::deleteSchedule()
{
    if(selectedIndex == -1) {return false;}
    s[selectedIndex]->hide();
    return true;
}

//重写鼠标点击事件
void dayWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->x() % DX;
    int y = event->y()-45;
    if( x>15 && x<63 && y>0 && event->x()<560)
    {
        if(tag == 1)//如果是当月日历
        {
            if(selectedIndex != todayIndex && selectedIndex != -1)
                qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
            selectedIndex = ((event->y()-45) / DY) * 7 + (event->x()/DX);
            if(selectedIndex != todayIndex)
                qlabel_group[selectedIndex]->setStyleSheet("border-image: url(:/res/whiteBorder.png)");
        }
        else//如果是其它月
        {
            if(selectedIndex != -1)
                qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
            selectedIndex = ((event->y()-45) / DY) * 7 + (event->x()/DX);
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url(:/res/whiteBorder.png)");
        }
    }
}
