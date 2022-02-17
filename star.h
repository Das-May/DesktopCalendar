#ifndef STAR_H
#define STAR_H

#include <QLabel>
#include <QTimer>

class Star : public QLabel
{
    Q_OBJECT
public:
    //重写构造函数
    Star (QWidget *parent = nullptr);

    //重写鼠标进入事件
    void enterEvent(QEvent *event);
    //重写鼠标离开事件
    void leaveEvent(QEvent *event);

    //属性
    QTimer  *timer;
    int num = 1;



signals:
    void enter();

public slots:
};

#endif // STAR_H
