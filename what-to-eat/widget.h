#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mysql.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //绘画事件
  void  paintEvent(QPaintEvent *ev);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
