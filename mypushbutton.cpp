#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QIcon>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg, QString hoverImg)
{
    //维护路径
    this->normalImgPath = normalImg;
    this->hoverImgPath = hoverImg;

    //获取、加载图片
    QPixmap pix;
    bool ret = pix.load(normalImg);//返回值是布尔类型，反馈图片是否加载成功
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setIcon(QIcon(pix));
    //this->setIconSize(pix.width(),pix.height());
    //设置图片固定大小  以免拖拉变形
    this->setFixedSize(40,40);

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);

    setAttribute(Qt::WA_AlwaysShowToolTips);

}

//重写鼠标进入事件
void MyPushButton::enterEvent(QEvent *event)
{
    if(hoverImgPath != "")
    {
        setStyleSheet("QPushButton{background-color:rgb(254,83,57)}");
    }
//    if(explanation != "")
//    {
//        setToolTip(explanation);
//    }
}

//重写鼠标离开事件
void MyPushButton::leaveEvent(QEvent *event)
{
    if(hoverImgPath != "")
    {
        setStyleSheet("QPushButton{background-color:rgba(254,83,57,0)}");
    }
}
