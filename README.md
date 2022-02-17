# DesktopCalendar
c++课程项目作业-桌面日历

一、系统的主要功能及实现思路

1、能按年、月、日的方式显示日历，能以时分秒的形式显示时间

实现思路：
以gettime.h作为算法处理类，输出历法。
新建一个QstackedWidget控件，在其中添加四个子窗口，分别是当月日历ThisDaysWidget、月份MonthWidget、年份YearWidget、其它月的日历ThatDaysWidget。设置当月日历是因为，此日历面板是最常使用的，如果每次查看都用算法初始化一次，会消耗不必要的内存，故单独设置为固定不变的窗口。四个窗口都用gettime.h提供的接口进行初始化。
新建一个QLabel控件，利用time.h提供的系统时间、gettime.h进行字符串处理的接口，和定时器，实现每秒更新一次时分秒时间。

![1](https://user-images.githubusercontent.com/92628959/154480526-9504367d-f80f-4546-8059-69ce74bb81cd.png)
![2](https://user-images.githubusercontent.com/92628959/154480764-1e6d7f4d-8cdc-4a9e-8232-846b08944a4f.png)



  
2、能显示农历和节假日

实现思路：以lunarcalendar.h作为算法处理类，运用比特位操作，输出阴历。
 ![3](https://user-images.githubusercontent.com/92628959/154480788-060d1731-c08c-4673-baa3-5f778c0ccf2a.png)


3、隐藏至托盘显示

实现思路：利用QsystemTrayIcon创建一个系统托盘，实现点击关闭按钮时，程序并非关闭而是最小化到托盘，点击托盘时再现程序。再用控件创建菜单项动作，实现右键显示“退出”按钮，真正地退出程序。
 ![4](https://user-images.githubusercontent.com/92628959/154480819-36cb9f33-d4ec-4320-8645-d3820e737bf5.png)




二、界面设计

制作流程：①用PS设计UI；②用cutterman切图工具切出UI素材；③在Qt中导入资源文件；④在PS中用标尺量出控件之间的距离，在Qt中用#define定义距离常量，用move()实现排版。
 
 ![5](https://user-images.githubusercontent.com/92628959/154480841-b5a04842-6335-47ae-bb80-4675d947e7b6.png)

 
这是我第一次独立设计UI！一直十分狂热地喜欢蓝黄配色，也很喜欢星月主题，于是此日历的UI主题就这样果断地定下来了。
背景是星空。程序员免不了加班熬夜，休息时抬头看向窗外，看得到星星的为未来思量，看不到星星的为当下惆怅。“我们的征途是星辰大海”寄寓了多少工科人的野心。深蓝色是温柔的颜色，希望用户在看到这款日历的时候能引发一些温暖地遐想。

功能实现上，核心日历被展示在中央偏左，按钮被安排在了右边和上面。点击展示“某年某月某日”的按钮可以回归当月日历；点击向左的按钮可以查看上一级日历；点击向上的按钮可以查看上个月/年的日历；向下同理。


三、结果展示

![8](https://user-images.githubusercontent.com/92628959/154482074-8105d270-76e3-4ce8-9807-2938549b555d.jpg)

