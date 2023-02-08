#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//line clipping by ajinkya 21252
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
    void on_pushButton_2_clicked();
    void draw_line(int x1, int y1, int x2, int y2, QRgb value);
    void drawwindow();
    int computeCode(double x, double y);
    void cohenSutherlandClip(double x1, double y1,double x2, double y2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
