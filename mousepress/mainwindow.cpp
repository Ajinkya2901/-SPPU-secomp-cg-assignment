#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include <iostream>
#include <QTimer>
#include <QTime>
#include "QColorDialog"
static QColor color;
using namespace std;

QImage img(700,700,QImage::Format_RGB888);

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

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (start){
     int p = ev->pos().x();
     int q = ev->pos().y();
     a[ver] = p;
     b[ver] = q;
     if (ev->button()==Qt::RightButton)
     {
     dda(a[0], b[0] , a[ver-1] , b[ver-1]);
     start = false;
     }
     else{
     if (ver>0){
     dda(a[ver],b[ver],a[ver-1],b[ver-1]);
     }
     }
     ver++;
     }
}


void MainWindow::on_pushButton_clicked()
{
    int dx, dy , i , k , temp , xi ;
    a[ver] = a[0];
     b[ver] = b[0];
     for (i=0;i<ver;i++){
     //Calculation of slope of each line
     dy = b[i + 1] - b[i];
     dx = a[ i + 1] - a[i];
     if (dy == 0.0f) slope[i] = 1.0;
     if (dx == 0.0f) slope[i] = 0.0;
     if ((dy != 0.0f) && (dx != 0.0f)){
     slope[i] = (float)dx/dy;
     } // calculate inverse slope
     }
     for (int y = 0; y<500; y++){
     k = 0;
     for (i=0;i<ver;i++){
     if (((b[i]<=y) && (b[i+1]>y)) || ((b[i] > y) && (b[i+1] <=
    y))){
     xi[k] = int(a[i] + (slope[i] * (y - b[i])));
     k++;
     }
     }
     for (j=0;j<k-1;j++)
     for (i = 0; i<k-j-1;i++){
     if (xi[i] > xi[i+1]){
     temp = xi[i];
     xi[i] = xi[i+1];
     xi[i+1] = temp;
     }
     }
     for (i = 0; i < k; i+=2){
     //delay(40);
     dda(xi[i] , y , xi[i+1] + 1 , y);
     }
    }
     ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    color = QColorDialog::getColor();
}

