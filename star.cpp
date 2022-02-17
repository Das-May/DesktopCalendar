#include "star.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPixmap>

//Star::Star(QWidget *parent) : QLabel(parent)
//{

//}

//重写构造函数
Star::Star (QWidget *parent)
{
    this->setParent(parent);
    //初始化星星
    QString img = ":/res/star1.png";
    QPixmap pix;
    bool ret = pix.load(img);
    if(!ret){
        QString str = QString("图片 %1 加载失败").arg(img);
        qDebug()<< str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setPixmap(pix);

    //初始化定时器对象
    timer = new QTimer(this);

    //监听定时器信号，从而执行动画
    connect(timer,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/star%1.png").arg(this->num++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setPixmap(pix);
        //判断 循环
        if(this->num > 4){
            this->num = 1;
        }
    });

}



//重写鼠标进入事件
void Star::enterEvent(QEvent *event)
{
    qDebug()<<"鼠标进入星星了";
    timer->start(100);//没0.1秒切换一次动画帧
    emit this->enter();
}

//重写鼠标离开事件
void Star::leaveEvent(QEvent *event)
{
    qDebug()<<"鼠标离开星星了";
    timer->stop();
}


