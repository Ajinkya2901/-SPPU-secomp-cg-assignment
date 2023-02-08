#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage img(1000 ,1000, QImage::Format_RGB444);

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

void MainWindow:: DDA(int x1 , int y1 , int x2 ,int y2 )
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float step = abs(dx)> abs(dy) ? abs(dx) : abs(dy) ;
    float x_inc = dx/step;
    float y_inc = dy /step;
    float x = x1;
    float y = y1;

    for(int i = 0 ; i < step ;i++)
    {
        img.setPixel(x , y , qRgb(250  ,250 , 250  ));
        x += x_inc;
        y += y_inc;

    }
}

void MainWindow::circle(int xc, int yc, int r)
{
    int x = 0 ; int y = r;

    int d = 3 - 2 * r;
    draw(xc ,yc ,x , y);
    while(y>=x)
    {
        x++;
        if(d>0)
        {
            d = d + 4 *(x-y) + 10;
            y--;
        }
        else{
            d = d + 4 * x + 6;
        }
        draw(xc ,yc ,x , y);
    }


}

void MainWindow::draw(int xc, int yc, int x, int y)
{
    img.setPixel(xc+x , yc+y , qRgb(250 , 0 , 0));
    img.setPixel(xc-x , yc+y , qRgb(250 , 0 , 0));
    img.setPixel(xc-x , yc-y , qRgb(250 , 0 , 0));
    img.setPixel(xc+x , yc-y , qRgb(250 , 0 , 0));
    img.setPixel(xc+y , yc+x , qRgb(250 , 0 , 0));
    img.setPixel(xc+y, yc-x , qRgb(250 , 0 , 0));
    img.setPixel(xc-y , yc+x , qRgb(250 , 0 , 0));
    img.setPixel(xc-y , yc-x, qRgb(250 , 0 , 0));
}
void MainWindow::on_pushButton_clicked()
{
    int Xc = ui->plainTextEdit->toPlainText().toInt();
    int Yc = ui->plainTextEdit_2->toPlainText().toInt();
    int r = ui->plainTextEdit_2->toPlainText().toInt();
    circle(Xc, Yc , r);
    DDA(Xc  , Yc - r  , Xc   - (r* 1.75)/2, Yc + r/2 );
    DDA( Xc   - (r* 1.75)/2, Yc + r/2 ,Xc  +(r* 1.75)/2 , Yc +r/2  );
     DDA( Xc +(r* 1.75)/2  , Yc+r/2 , Xc  , Yc -r );
     circle(Xc, Yc , r/2);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

