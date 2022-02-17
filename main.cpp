#include "desktopcalendar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopCalendar w;
    w.show();

    return a.exec();
}
