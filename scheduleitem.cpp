#include "scheduleitem.h"
#include "ui_scheduleitem.h"
#include "star.h"
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

ScheduleItem::ScheduleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);
    Star *s = new Star(this);

    ui->label->hide();

    connect(s,&Star::enter,[=](){
        ui->label->show();
    });

    ui->label->installEventFilter(this);
}

////事件过滤器
//bool ScheduleItem::eventFilter(QObject* obj, QEvent* evt)
//{
//    if (obj == ui->label)
//    {
//        if (evt->type() == QEvent::MouseButtonDblClick)
//        {
//            ui->textEdit->setText(ui->label->text());
//            ui->stackedWidget->setCurrentIndex(1);
//            return true;
//        }
//    }
//    else if (obj == ui->textEdit)
//    {
////        if (evt->type() == QEvent::KeyPress)
////        {
////            QKeyEvent* keyevt = static_cast<QKeyEvent*>(evt);
////            if ((keyevt->key() == Qt::Key_Return) ||
////                (keyevt->key() == Qt::Key_Escape) ||
////                (keyevt->key() == Qt::Key_Enter))   // Qt::Key_Return是大键盘的回车键 Qt::Key_Enter是小键盘的回车键
////            {
////                ui->label->setText(ui->textEdit->toPlainText());
////                ui->stackedWidget->setCurrentIndex(0);
////                return true;
////            }
////        }
////        else
//        if (evt->type() == QEvent::FocusAboutToChange)
//        {
//            ui->label->setText(ui->textEdit->toPlainText());
//            ui->stackedWidget->setCurrentIndex(0);
//            return true;
//        }
//    }

//    return QWidget::eventFilter(obj, evt);//非常重要！返回的是基类的原函数，而不是自身的
//    //在这里吃了很久很久的亏
//}


//重写鼠标离开事件
void ScheduleItem::leaveEvent(QEvent *event)
{
    ui->label->hide();
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}
