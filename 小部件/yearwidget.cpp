#include "yearwidget.h"
#include <QLabel>
#include <QPalette>
#include <QDebug>
#include <QFont>

#define dx 154
#define dy 63
#define w 95
#define h 46

//重写构造函数
YearWidget::YearWidget(QWidget *parent, int year)
{
    this->setFixedSize(586, 302);
    tag = 0;  //翻找次数默认为0
    selectedIndex = 0;
    QFont f("Microsoft YaHei", 10, 70);//设置字体、字号 微软雅黑 8号
    ///////初始化int数组///////
    //设1970年为第一年，那么year就是第year-1970年
    //16格为一页，那么year在其当页的 第(year-1970)%16格(索引号)    第(year-1970)%16/4行、第(year-1970)%16%4列
    //那么当页的第一格为year-((year-1970)%16)
    int num = year - (( year - 1970 ) % 16 );
    for(int i = 0; i < 16; i++)
    {
        yearArray[i] = num++;
    }

    ///////初始化QLabel数组////////
    int index = 0;
    QPalette  whitePe;//设置字体颜色 白色
    whitePe.setColor(QPalette::WindowText,Qt::white);
    for(; index < 16; index++)
    {
        qlabel_group.push_back(new QLabel(this));
        qlabel_group[index]->setFixedSize(w, h);//设置标签大小
        qlabel_group[index]->setPalette(whitePe);//设置文字颜色
        qlabel_group[index]->setFont(f);//设置文本字体、字号
        qlabel_group[index]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置文字对齐方式
    }

    ////////初始化内容/////////
    ifoUi();
}

//设置内容
void YearWidget::ifoUi()
{
    for(int index = 0; index < 16; index++)  //对应第index/4行，index%4列
    {
        qlabel_group[index]->setText(QString::number(yearArray[index] + 16 * tag));
        qlabel_group[index]->move( 30 + dx * (index%4), 42 + dy * (index/4) );//列  行
    }
}

//重写鼠标点击事件
void YearWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)//如果点到了年份
    {
        qDebug()<<"按下鼠标";
        int x = event->x() % dx;
        int y = event->y()-42;
        if( x>30 && x<124 && y>0)
        {
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");
            selectedIndex = ((event->y()-42) / dy) * 4 + (event->x()/dx);
            qlabel_group[selectedIndex]->setStyleSheet("border-image: url(:/res/whiteBorder.png)");
        }
    }
}

//重写鼠标双击事件
void YearWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug()<<"双击";
        int x = event->x() % dx;
        int y = event->y()-42;
        if( x>30 && x<124 && y>0)
        {
            selectedIndex = ((event->y()-42) / dy) * 4 + (event->x()/dx);
            y = qlabel_group[selectedIndex]->text().toInt();//QString转Int
            emit this->yearChoosed( y );//发出已有年份被双击选中的信号
        }
        qlabel_group[selectedIndex]->setStyleSheet("border-image: url()");//取消选择
    }
}


///////设置翻找次数///////
void YearWidget::setTagMore()
{
    ++tag;
}//增加

void YearWidget::setTagLess()
{
    --tag;
}//减少

void YearWidget::setTagIfo()
{
    tag = 0;
}
