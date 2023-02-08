#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <math.h>
//#include <graphics.h>
using namespace std;

QImage img(1000 , 1000 ,QImage :: Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QRgb blue = qRgb(0 , 0 ,255);
QRgb green = qRgb(0 , 255 ,0);
QRgb red = qRgb(255 , 0 ,0);

void MainWindow::draw_line(int x1 ,int y1,int x2 ,int y2 ,QRgb value)
{
    float dx , dy  ;
    dx = x2 - x1 ;
    dy = y2 - y1;
    float len = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx/len;
    float y_inc = dy/len;
    float x = x1;
    float y = y1;

    for(int i = 0; i<len ; i++){
        x += x_inc;
        y += y_inc;
        img.setPixel(x , y ,value);
    }
}

//    DDALine(x0, y0, x1, y1);


void MainWindow::koch(int it,int x1,int y1,int x5,int y5)
{
    int x2,y2,x3,y3,x4,y4;
    int dx,dy;

    if (it==0)
    {
        draw_line(x1,y1,x5,y5 ,green);
    }
    else
    {
//                delay(10);

        dx=(x5-x1)/3;
        dy=(y5-y1)/3;

        x2=x1+dx;
        y2=y1+dy;

        x3=(int)(0.5*(x1+x5)+sqrt(3)*(y1-y5)/6);
        y3=(int)(0.5*(y1+y5)+sqrt(3)*(x5-x1)/6);

        x4=2*dx+x1;
        y4=2*dy+y1;

        koch(it-1,x1,y1,x2,y2);
        koch(it-1,x2,y2,x3,y3);
        koch(it-1,x3,y3,x4,y4);
        koch(it-1,x4,y4,x5,y5);
    }
}


//    kochCurve k;
//    int it;
//    cout<<"Enter Number Of Iterations : "<<endl;
//    cin>>it;
//    int gd=DETECT,gm;
//    initgraph(&gd,&gm,NULL);
//    koch(5,150,20,20,280);
//    koch(it,280,280,150,20);
//    koch(it,20,280,280,280);



void MainWindow::on_pushButton_clicked()
{
    int it = 2;           //change this for more curve
    koch(it,150,20,20,280);
    koch(it,20,280,280,280);
    koch(it,280,280,150,20);
    ui->label->setPixmap(QPixmap ::fromImage(img));
}
