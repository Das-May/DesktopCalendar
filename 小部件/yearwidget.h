#ifndef YEARWIDGET_H
#define YEARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "gettime.h"

class YearWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit YearWidget(QWidget *parent = nullptr);
    YearWidget(QWidget *parent = nullptr, int year = 1970);    //重写构造函数

    void ifoUi();    //设置界面

    //设置翻找次数
    void setTagMore();  //增加
    void setTagLess();  //减少
    void setTagIfo();//置零

    void mousePressEvent(QMouseEvent *event);    //重写鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);    //重写鼠标双击事件

private:
    int yearArray[16]; //年份int数组 4行4列
    QVector<QLabel*> qlabel_group; //年份QLabel数组
    int tag;//翻找次数

    int yearSelected;//被选中的年份
    int selectedIndex;//被选中的标签的索引号


signals:
    void yearChoosed(int y);//信号 已有年份被双击选中

public slots:
};

#endif // YEARWIDGET_H
