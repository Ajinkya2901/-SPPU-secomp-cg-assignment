//line clipping by ajinkya 21252
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

QImage image(500 ,500,QImage :: Format_RGB888);

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


const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000

int x_max = 100;
int y_max = 80;
int x_min = 40;
int y_min = 40;
//int x_max;
//int y_max;
//int x_min;
//int y_min;

// x_max, y_max and x_min, y_min for
//clipping rectangle.
//const int x_max = 100;
//const int y_max = 8;
//const int x_min = 4;
//const int y_min = 4;

void MainWindow::draw_line(int x1, int y1, int x2, int y2, QRgb value){

    float x_inc, y_inc, dx, dy, x, y;
    dx = x2-x1;
    dy = y2-y1;
    int len = abs(dx)>abs(dy)? abs(dx):abs(dy);
    x_inc = dx / len;
    y_inc = dy / len;
    x = x1;
    y = y1;
    for(int i=0; i<len; i++){
        image.setPixel(x, y, value);
        x += x_inc;
        y += y_inc;
    }
}

void MainWindow :: drawwindow(){
     int x_max = 100;
     int y_max = 80;
     int x_min = 40;
     int y_min = 40;

//    int x_min  = ui->plainTextEdit->toPlainText().toInt();
//    int y_min  = ui->plainTextEdit_2->toPlainText().toInt();
//    int x_max  = ui->plainTextEdit_3->toPlainText().toInt();
//    int y_max  = ui->plainTextEdit_4->toPlainText().toInt();

     QRgb red;
     red = qRgb(255,0 , 0);

//     QRgb green;
//     green=qRgb(0,255,0);
     draw_line(x_min,y_min , x_max , y_min , red);
     draw_line(x_max , y_min , x_max , y_max, red);
     draw_line(x_max , y_max, x_min, y_max, red) ;
     draw_line(x_min, y_max , x_min,y_min , red);
}

// compute region code for point(x, y)
int MainWindow :: computeCode(double x, double y)
{
//    int x_min  = ui->plainTextEdit->toPlainText().toInt();
//    int y_min  = ui->plainTextEdit_2->toPlainText().toInt();
//    int x_max  = ui->plainTextEdit_3->toPlainText().toInt();
//    int y_max  = ui->plainTextEdit_4->toPlainText().toInt();
    // initialized as being inside
    int code = INSIDE;

    if (x < x_min) // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min) // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;

    return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x2, y2) to P2 = (x2, y2)
void MainWindow :: cohenSutherlandClip(double x1, double y1,double x2, double y2)
{
//    int x_min  = ui->plainTextEdit->toPlainText().toInt();
//    int y_min  = ui->plainTextEdit_2->toPlainText().toInt();
//    int x_max  = ui->plainTextEdit_3->toPlainText().toInt();
//    int y_max  = ui->plainTextEdit_4->toPlainText().toInt();
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2) {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Now intersection point x, y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    QRgb red;
    red = qRgb(255,0 , 0);
    if (accept) {
        draw_line(x1 , y1,x2,y2 ,red);
        cout << "Line accepted from " << x1 << ", "
            << y1 << " to " << x2 << ", " << y2 << endl;
        // Here the user can add code to display the rectangle
        // along with the accepted (portion of) lines
    }
    else
        cout << "Line rejected" << endl;
}

//int main()
//{
    // First Line segment
    // P11 = (5, 5), P12 = (7, 7)
//    cohenSutherlandClip(5, 5, 7, 7);

    // Second Line segment
    // P21 = (7, 9), P22 = (11, 4)
//    cohenSutherlandClip(7, 9, 11, 4);

    // Third Line segment
    // P31 = (1, 5), P32 = (4, 1)
//    cohenSutherlandClip(1, 5, 4, 1);

//}


void MainWindow::on_pushButton_clicked()
{
    drawwindow();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    cohenSutherlandClip(50, 50, 70, 70);
    cohenSutherlandClip(70, 90, 110, 40);
    cohenSutherlandClip(10, 50, 50, 50);
    cohenSutherlandClip(50, 20, 50, 500);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
