#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void DDA(int y1 , int x1 , int x2 ,int y2 );
    void circle(int xc , int yc , int r);
    void draw(int xc ,int yc , int x , int y);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
