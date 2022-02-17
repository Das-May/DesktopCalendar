#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //重写构造函数
    MyPushButton(QString normalImg, QString hoverImg = "");

    //成员属性
    QString normalImgPath;
    QString hoverImgPath;

    //重写鼠标进入事件
    void enterEvent(QEvent *event);
    //重写鼠标离开事件
    void leaveEvent(QEvent *event);

    //重写鼠标进入事件



signals:

public slots:
};

#endif // MYPUSHBUTTON_H
