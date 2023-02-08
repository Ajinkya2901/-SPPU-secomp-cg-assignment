#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include <iostream>
#include<QTime>
#include<QtDebug>
#include"QColorDialog"
using namespace std;
QImage img(1000 , 1000 , QImage::Format_RGB888);
QColor colour;
QColor bgcolor = qRgb(0 , 0, 0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
//void MainWindow::delay(int militowait)
//{
//    QTime die = QTime::currentTime().addMSecs(militowait);
//    while(QTime::currentTime()  < die)
//    {
//        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
//    }
//}

void MainWindow::draw_line(int x1, int y1, int x2, int y2)
{
    float dx = x2 -x1 ;
    float dy = y2 - y1 ;

    int len = abs(dx) > abs(dy) ? abs(dx) : abs(dy) ;

    float x_inc = dx/len;
    float y_inc = dy /len ;
    float x = x1;
    float y = y1;
    for(int i = 0 ; i<len ; i++){
        img.setPixel(x , y , colour.rgb());
        x += x_inc;
        y += y_inc;

    }

}

void MainWindow::draw_polygon()
{
//    float x1[] = {100,200,400,400,100,100};
//    float y1[] = {100,250,100,400,400,100};

    for(int i = 0 ; i < ver  ; i++){
        draw_line(x1[i] , y1[i] , x1[i+1] , y1[i+1]);
    }

}

void MainWindow::scan_fill()
{


    x1[ver] = x1[0];
    y1[ver] = y1[0];
    float ymin = INT_MAX;
    float ymax = INT_MIN;

    int n = ver ;
    float m[100] , a[100];

    for(int i = 0; i < n ; i++)
    {
        if(y1[i] > ymax){
            ymax = y1[i];
        }
        if(y1[i] < ymin){
            ymin = y1[i];
        }
        float dx = x1[i+1] - x1[i];
        float dy = y1[i+1] - y1[i];
        if(dx == 0){
            m[i] = 0;
        }

        if(dy == 0){
            m[i] = 1;
        }
        if( dx!=0 && dy !=0){
            m[i] = dx/dy;
        }
    }

    int c =0;
    int y ;
    for( y = ymax ;  y > ymin ; y--)
    {


        int c =0;
        for(int j = 0 ; j < n ; j++)
        {
            if(  (y1[j] >y && y >= y1[j+1] ) || (  y1[j] <=y  && y < y1[j +1 ]))
            {
                a[c] = ((y - y1[j]) * m[j] ) + x1[j];
                cout << a[c] << " ";
                c++;
            }
        }
        cout << endl;



        int t;
        for(int i=0 ;i < c-1;i++)
        {
          for(int j= 0;j < c - i - 1;j++)
          {
              if(a[j]>a[j+1])
              {
                  t=a[j];
                  a[j]=a[j+1];
                  a[j+1]=t;
              }
          }
        }

        for( int i = 0 ; i < c-1 ;i = i+2)
        {
            draw_line(a[i] , y  ,a[i+1],y );
            delay(10);
            ui->label->setPixmap(QPixmap :: fromImage(img));
        }
    }

}


void MainWindow::on_pushButton_clicked()
{
    draw_polygon();
    ui->label->setPixmap(QPixmap :: fromImage(img));
}

void MainWindow::on_pushButton_2_clicked()
{
    scan_fill();
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    cout << "atar";
    if(start)
    {
        int p = ev->pos().x();
        int q = ev->pos().y();
        cout << p << " " << q;
        x1[ver] = p;
        y1[ver] = q;
        if(ev->button() == Qt::RightButton)
        {
//            x1[ver] = x1[0];
//            y1[ver] = y1[0];
             draw_line( x1[0], y1[0], x1[ver-1], y1[ver-1]);
            start = false;
        }
        else {
            if(ver > 0 )
            {
                draw_line(   x1[ver-1], y1[ver-1] , x1[ver], y1[ver]);
            }

        }
        ver++;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    scan_fill();
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::delay(int m)
{
    QTime die = QTime::currentTime().addMSecs(m);
    while(die.currentTime() < die)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    cout << "hit";
    colour = QColorDialog :: getColor();
}

void MainWindow::on_pushButton_4_clicked()
{
    img.fill(bgcolor);
    start = 1;
    ver = 0;
    ui->label->setPixmap(QPixmap::fromImage(img));
}


// 1 click to slect points and 2 click to draw and fill polygon
