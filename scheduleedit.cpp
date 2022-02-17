#include "scheduleedit.h"
#include "ui_scheduleedit.h"
#include <QPainter>

ScheduleEdit::ScheduleEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScheduleEdit)
{
    ui->setupUi(this);

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/pixLabel.png");
    ui->pixLabel->setPixmap(pix);
}

//设置日期
void ScheduleEdit::setDate(int y, int m, int d)
{
    QString text1;
    text1.append("<p style='marign:50px'>").append(QString::number(y) + "年").append("</p>");//怎么设置字间距啊？！
    ui->yLabel->setText(text1);
    ui->mdLabel->setText(QString::number(m) + "月" + QString::number(d) + "日");
}
ScheduleEdit::~ScheduleEdit()
{
    delete ui;
}

