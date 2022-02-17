#include "mytable.h"
#include <QStringList>

MyTable::MyTable(QWidget *parent) : QTableWidget(parent)
{
    calendar = new QTableWidget(this);

    calendar->setRowCount(7);//设置行数
    calendar->setColumnCount(7);//设置列数
    calendar->set(610,268);//设置尺寸

    //设置表头
    QStringList header;
    header<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
    calendar->setHorizontalHeaderLabels(header);

}
