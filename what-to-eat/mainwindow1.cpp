//////////////显示开始界面
#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "QPushButton"
#include "widget.h"
#include "QPainter"
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    setWindowTitle("选择困难者的福音");
    setWindowOpacity(1);//设置透明度
    ui->pushButton->move((this->width()-100)*0.5,this->height()*0.5+50);
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        Widget *W=new Widget;
        this->close();
        W->show();
    });
}
void  MainWindow1::paintEvent(QPaintEvent *ev)
{
    //绘画出背景
    QPainter painter(this);
    painter.drawPixmap(0,0,600,300,QPixmap(":/imge/beijin.png"));
    painter.drawPixmap(10,10,50,50,QPixmap(":/imge/user.png"));
}
MainWindow1::~MainWindow1()
{
    delete ui;
}
