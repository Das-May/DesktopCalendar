#include "desktopcalendar.h"   //自身头文件
#include "ui_desktopcalendar.h"   //ui文件
#include <QMenu>
#include <QAction>
#include <QFile>

#include <QPainter>  //画家类
#include <QPixmap>   //图像类
#include <QLabel>   //控件 标签类
#include <QTimer>   //定时器类
#include <QPalette>   //调色类
#include <QFont>   //字体类
#include <QColor>    //颜色类
#include <QRect>

#include <time.h>   //系统 时间类
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QDebug>
#include <QSystemTrayIcon>  //主要操作系统托盘的操作类


//构造函数
DesktopCalendar::DesktopCalendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopCalendar)
{
    ui->setupUi(this);
    gt = new GetTime(this);

    ///////////////①配置窗体///////////////
    //设置固定大小
    setFixedSize(680,446);
    //设置窗口置顶
    setWindowFlags(Qt::WindowStaysOnTopHint);
    //隐藏功能键  这将导致窗口无法被拖拽，需要重写鼠标事件
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    //隐藏任务栏图标
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);


    /////////////②加载日历主体（栈窗口）//////////////////
    //初始化
    thisDaysWidget = new dayWidget(this, gt);
    monthWidget = new MonthWidget(this, gt->getYear());
    yearWidget = new YearWidget(this, gt->getYear());
    thatDaysWidget = new dayWidget(this, gt);
    edit = new ScheduleEdit(this);

    //当月日历 0
    ui->stackedWidget->insertWidget( 0, thisDaysWidget);


    //月历 1  
    ui->stackedWidget->insertWidget(1, monthWidget);
    connect(monthWidget,&MonthWidget::monthChoosed,gt,&GetTime::setM);
    connect(monthWidget,&MonthWidget::monthChoosed,[=](){
        this->gt->setMonthArray();
        this->thatDaysWidget->update(this->gt);
        ui->stackedWidget->setCurrentIndex(3);
    });

    //年历 2
    ui->stackedWidget->insertWidget(2, yearWidget);
    connect(yearWidget,&YearWidget::yearChoosed,monthWidget,&MonthWidget::changeYear);
    connect(yearWidget,&YearWidget::yearChoosed,gt,&GetTime::setY);
    connect(yearWidget,&YearWidget::yearChoosed,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    //其它月 3
    ui->stackedWidget->insertWidget(3, thatDaysWidget);

    //日程表
    ui->stackedWidget->insertWidget(4,edit);

    ui->stackedWidget->move(22, 132);
    ui->stackedWidget->setCurrentIndex(0);

    ///////////③日历面板////////////////
    //时分秒 hour minute second
    QPalette  whitePe;//设置字体颜色 白色
    whitePe.setColor(QPalette::WindowText,Qt::white);
    QTimer * HMS_timer = new QTimer;
    ui->hmsLabel->setPalette(whitePe);
    ui->hmsLabel->setText(gt->getHMS());//初始化显示
    connect(HMS_timer,&QTimer::timeout,this,&DesktopCalendar::HMS_show);//实现每秒更新
    HMS_timer->start(1000);

    //年月日 year month day
    ui->ymdBtn->setText(gt->getYMD());
    connect(ui->ymdBtn,&QPushButton::clicked,[=](){
        yearWidget->setTagIfo();//重置年份面板
        yearWidget->ifoUi();
        ui->stackedWidget->setCurrentIndex(0);//回归今日日历
    });


    //////////////配置功能键///////////////
    buttonInfo();

    ///////////最小化到托盘//////
    mini();

//    ///////////日程记录//////
//    QFile f(":/res/calendar.txt");
//    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug() << "文件打开失败." ;
//    }

//    QTextStream txtInput(&f);
//    txtInput.setCodec("UTF-8");//设置UTF-8编码读取  确保读取时不会乱码
//    while(!txtInput.atEnd())
//    {
//        calendar << txtInput.readLine();
//    }
//    qDebug() << calendar ;
//    f.close();

//    //日程表提示
//    QStringList str;
//    str << QString::number(gt->getYear()) <<"-" << QString::number(gt->getMonth());
//    if(calendar.contains(str))
//    {

//    }
}

//绘制背景图
void DesktopCalendar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

//配置功能键
void DesktopCalendar::buttonInfo()
{
    //加载关闭按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/close.png",":/res/closeBackground.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-50, 0);
    closeBtn->setFixedSize(50, 50);
    connect(closeBtn,&MyPushButton::clicked,[=](){
        this->close();
    });
    closeBtn->raise();//置顶关闭按钮

    //加载往前翻按钮
    MyPushButton * backBtn = new MyPushButton(":/res/backButton.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-40, 101);
    backBtn->setToolTip("上一级");
    connect(backBtn,&MyPushButton::clicked,[=](){
        int index = ui->stackedWidget->currentIndex();
        switch (index) {
        case 0:  //如果当前在当月的日历
            ui->stackedWidget->setCurrentIndex(1);//则转到月历
            break;
        case 1:  //如果当前在月历
            ui->stackedWidget->setCurrentIndex(2);//则转到年历
            break;
        case 3:  //如果当前在其他日历
            monthWidget->setYear(gt->getY());
            ui->stackedWidget->setCurrentIndex(1);//则转到月历
            break;
        case 4://如果当前在日程编辑页
            ui->stackedWidget->setCurrentIndex(beforeIndex);//则转到"之前的"历
            break;
        default:
            break;
        }
    });


    //加载往上翻按钮
    MyPushButton * lastBtn = new MyPushButton(":/res/lastButton.png");
    lastBtn->setToolTip("上一页");
    lastBtn->setParent(this);
    lastBtn->move(this->width()-40, 159);
    connect(lastBtn,&MyPushButton::clicked,[=](){
        int index = ui->stackedWidget->currentIndex();
        if(index == 2)//如果当前在年历
        {
            yearWidget->setTagLess();
            yearWidget->ifoUi();
        }
        else if(index == 0)//如果当前在日历
        {
            gt->setData(gt->getMonth() - 1);
            gt->setMonthArray();
            thatDaysWidget->update(gt);
            ui->stackedWidget->setCurrentIndex(3);

        }
        else if(index == 3)//如果在其他月的日历
        {
            gt->setData(gt->getM() - 1);
            gt->setMonthArray();
            thatDaysWidget->update(gt);
        }
    });



    //加载往下翻按钮
    MyPushButton * nextBtn = new MyPushButton(":/res/nextButton.png");
    nextBtn->setParent(this);
    nextBtn->move(this->width()-40, 212);
    nextBtn->setToolTip("下一页");
    connect(nextBtn,&MyPushButton::clicked,[=](){
        int index = ui->stackedWidget->currentIndex();
        if(index == 2)  //如果当前在年历
        {
            yearWidget->setTagMore();
            yearWidget->ifoUi();
        }
        else if(index == 0)//如果当前在日历
        {
            gt->setData(gt->getMonth() + 1);
            gt->setMonthArray();
            thatDaysWidget->update(gt);
            ui->stackedWidget->setCurrentIndex(3);
        }
        else if(index == 3)
        {
            gt->setData(gt->getM() + 1);
            gt->setMonthArray();
            thatDaysWidget->update(gt);
        }
    });


/*    //加载添加事件按钮
    MyPushButton * addBtn = new MyPushButton(":/res/addButton.png");
    addBtn->setParent(this);
    addBtn->move(this->width()-40, 265);
    connect(addBtn,&MyPushButton::clicked,[=](){
        int i = ui->stackedWidget->currentIndex();
        if(i == 0)
        {
            if(this->thisDaysWidget->addSchedule())
            {
                beforeIndex = i;
                edit->setDate(gt->getYear(), gt->getM(), this->thisDaysWidget->getSeletedDay());
                ui->stackedWidget->setCurrentIndex(4);
            }
        }
        else if(i == 3)
        {
            if(this->thatDaysWidget->addSchedule())
            {
                beforeIndex = i;
                edit->setDate(gt->getYear(), gt->getM(), this->thatDaysWidget->getSeletedDay());
                ui->stackedWidget->setCurrentIndex(4);
            }
        }
        qDebug()<<"创建tips";
    });

    //加载删除事件按钮
    MyPushButton *deleteBtn = new MyPushButton(":/res/deleteButton.png");
    deleteBtn->setParent(this);
    deleteBtn->move(this->width()-40, 318);
    connect(deleteBtn,&MyPushButton::clicked,[=](){
        int i = ui->stackedWidget->currentIndex();
        if(i == 0)
            this->thisDaysWidget->deleteSchedule();
        else if(i == 3)
            this->thatDaysWidget->deleteSchedule();
    });
*/

}

//最小化到托盘
void DesktopCalendar::mini()
{

        //创建一个系统托盘
        QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
        trayIcon->setToolTip(tr("桌面日历"));   //设置鼠标移动到托盘图标显示的文本
        trayIcon->setIcon(QIcon(":/res/icon.png"));  //设置托盘图标
        trayIcon->show();

        //创建菜单项动作(以下动作只对windows有效)
        QMenu *trayIconMenu = new QMenu(this);

        QAction *restoreAction = new QAction("显示", this);
        connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

        QAction *quitAction = new QAction("退出", this);
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); //关闭应用，qApp对应的是程序全局唯一指针

        //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
        trayIconMenu = new QMenu(this);
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();  //分隔符
        trayIconMenu->addAction(quitAction);
        trayIcon->setContextMenu(trayIconMenu);

        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

        //绑定系统托盘的激活操作信号槽连接
        connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason)
        {
            switch (reason)
            {
                case QSystemTrayIcon::DoubleClick: /* 来自于双击激活。 */
                    this->show();
                    break;
                case QSystemTrayIcon::Trigger:     /* 来自于单击激活。 */
                    this->show();
                    break;
            }
        });
}


//重写鼠标按下事件
void DesktopCalendar::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
            clickPos=event->pos();
}

//重写鼠标移动事件
void DesktopCalendar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
            move(event->pos()+pos()-clickPos);

}

////重写鼠标释放事件
//void DesktopCalendar::mouseReleaseEvent(QMouseEvent *event)
//{
//    event->ignore();
//    if(resizeDir != nodir){         //还原鼠标样式
//        //testEdge();
//    }
//}

void DesktopCalendar::enterEvent(QEvent *event)
{

}

void DesktopCalendar::leaveEvent(QEvent *event)
{

}

//重写关闭
void DesktopCalendar::closeEvent(QCloseEvent *event)
{
    qDebug()<<"最小化到托盘";
    event->ignore();
    this->hide();
}

//展示时分秒
void DesktopCalendar::HMS_show()
{
    //必须每次重新获取系统时间 才可做到更新
    time_t st = time(NULL);//systerm time 系统时间
    char str[32];
    strftime( str, sizeof(str), "%H:%M:%S",localtime(&st) );
    ui->hmsLabel->setText(str);
}

DesktopCalendar::~DesktopCalendar()
{
    delete ui;
}

