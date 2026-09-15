#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include "widget.h"
#include <QMainWindow>
namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();

    //绘画事件
    void  paintEvent(QPaintEvent *ev);
private:
    Ui::MainWindow1 *ui;
};

#endif // MAINWINDOW1_H
