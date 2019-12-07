#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QMainWindow>

namespace Ui {
class SideBar;
}

class SideBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

private:
    Ui::SideBar *ui;
};

#endif // SIDEBAR_H
