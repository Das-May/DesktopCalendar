#ifndef SCHEDULEEDIT_H
#define SCHEDULEEDIT_H

#include <QWidget>

namespace Ui {
class ScheduleEdit;
}

class ScheduleEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleEdit(QWidget *parent = 0);
    void setDate(int y, int m, int d);//设置日期
    ~ScheduleEdit();

private:
    Ui::ScheduleEdit *ui;
};

#endif // SCHEDULEEDIT_H
