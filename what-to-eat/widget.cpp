#include "widget.h"
#include "ui_widget.h"
#include "QString"
#include "QTime"
#include "QDebug"
#include "QPainter"
#include "mysql.h"
#include "QDebug"
#include "QFont"
#include "QMessageBox"
#include "globals.h"
bool South=false;
bool North=false;
bool Drink=false;
int ui_index=3;
QString str0=":/imge/beijin.png";
QString str1=":/imge/background_2.png";
QString str2=":/imge/drink_2.png";
QString str3=":/imge/addd.png";
//生成exe流程  打开QT对应的minGW  然后cd /d D:/QT/build-APP_Gandalf-Desktop_Qt_6_2_4_MinGW_64_bit-Release/release/APP_Gandalf.exe  最后windeployqt APP_Gandalf.exe
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("选择困难者的福音");
    setWindowOpacity(1);//设置透明度

    ///////////////////////////////////////////////////////初始界面
    ui->stackedWidget->setCurrentIndex(4);
    ////////////////////////////////////////////////////////////界面跳转
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        ui_index=0;
        ui->stackedWidget->setCurrentIndex(ui_index);//跳转到选菜界面
    });

    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        ui_index=1;
        ui->stackedWidget->setCurrentIndex(ui_index);//跳转到选饮料界面

    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=]()
            {
                ui_index=2;
                ui->stackedWidget->setCurrentIndex(ui_index);//跳转到添加界面-食物
            });
    connect(ui->pushButton_8,&QPushButton::clicked,[=]()
            {
                ui_index=5;
                ui->stackedWidget->setCurrentIndex(ui_index);//跳转到添加界面-饮
            });
    connect(ui->pushButton_14,&QPushButton::clicked,[=]()
            {
                if(ui_index>0)ui_index-=1;
                South=false;
                North=false;
                Drink=false;
                ui->stackedWidget->setCurrentIndex(ui_index);//返回上一级菜单
            });
    connect(ui->pushButton_5,&QPushButton::clicked,[=]()
            {
                ui_index=2;
                ui->stackedWidget->setCurrentIndex(ui_index);
            });//添加界面
    /// ////////////////////////////////////////添加界面设置
    // if(ui->textEdit1->document()->isEmpty())//判断是否textEdit是否为空的方法)
    QTextCharFormat format;
    format.setFontFamily("宋体");
    format.setFontPointSize(36);
    ui->textEdit1->textCursor().mergeBlockCharFormat(format);
    ui->textEdit2->textCursor().mergeBlockCharFormat(format);
    connect(ui->pushButton_12,&QPushButton::clicked,[=](){
        South=true;//添加南区食物
        North=false;
        Drink=false;
        ui_index=3;
        ui->stackedWidget->setCurrentIndex(ui_index);
    });
    connect(ui->pushButton_13,&QPushButton::clicked,[=](){
        North=true;//添加北区食物
        South=false;
        Drink=false;
        ui_index=3;
        ui->stackedWidget->setCurrentIndex(ui_index);
    });
    connect(ui->pushButton_11,&QPushButton::clicked,[=](){
        QString strTxtEdt = ui->textEdit1->toPlainText();
        if(strTxtEdt.length()==0)
        {
            QMessageBox::information(this,"提示","输入为空");
        }
        else
        {
            MySql MS;
            MS.InsertData(strTxtEdt,South,North,Drink);
            ui->textEdit1->clear();
        }
    });
    //添加饮料
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        Drink=true;
        North=false;
        South=false;
        ui_index=5;
        ui->stackedWidget->setCurrentIndex(ui_index);

    });
    connect(ui->pushButton_16,&QPushButton::clicked,[=](){
        QString strTexEdt3=ui->textEdit2->toPlainText();
        if(strTexEdt3.length()==0)
        {
            QMessageBox::information(this,"提示","输入为空");

        }
        else
        {
            MySql MS;
            MS.InsertData(strTexEdt3,South,North,Drink);
            ui->textEdit2->clear();
        }

    });
    ////////////////////////////////////////////////////////////////选择
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        South=true;
        North=false;
        Drink=false;
        MySql MS;
        if(MS.getNumber(South,North,Drink)==0)
        {
            QMessageBox::information(this, "提示", "未添加食物，数据库为空");
        }
        else
        {
            int INDEX = rand() % MS.getNumber(South,North,Drink)+1;
            QString South_Food=MS.ShowData(INDEX,South,North,Drink);
            ui->label->setText(QString(South_Food));

        }

    });//南区 South

    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        North=true;
        South=false;
        Drink=false;
        MySql MS;
        if(MS.getNumber(South,North,Drink)==0)
        {
            QMessageBox::information(this, "提示", "未添加食物，数据库为空");
        }
        else
        {
            int INDEX = rand() % MS.getNumber(South,North,Drink)+1;
            QString North_Food=MS.ShowData(INDEX,South,North,Drink);
            ui->label->setText(QString(North_Food));
        }
    });///北区 North

    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        Drink=true;
        North=false;
        South=false;
        MySql MS;
        if(MS.getNumber(South,North,Drink)==0)
        {
            QMessageBox::information(this, "提示", "未添加饮料，数据库为空");
        }
        else
        {
            int INDEX = rand() % MS.getNumber(South,North,Drink)+1;
            QString Drink_name=MS.ShowData(INDEX,South,North,Drink);
            ui->label_2->setText(QString(Drink_name));
        }
    });//选饮料  Drink

}
void  Widget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,600,300,QPixmap(str0));
    if(ui_index==0)
    {
        ui->stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget{border:2px solid black}"));//写出具体名字不然会影响子控件
        painter.drawPixmap(0,0,600,300,QPixmap(str1));
    }
    //绘画出背景
    if(ui_index==1)
    {
        ui->stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget{border:2px solid black}"));
        painter.drawPixmap(0,0,600,300,QPixmap(str2));
    }
    if(ui_index==2)
    {
        ui->stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget{border:2px solid black}"));
        painter.drawPixmap(0,0,600,300,QPixmap(str3));
    }

}
Widget::~Widget()
{
    delete ui;
}
