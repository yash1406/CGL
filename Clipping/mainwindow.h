#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    float sign(float);
    void dda_line(float,float,float,float);
    void mousePressEvent(QMouseEvent *);
    int computeCode(float,float);
    void cohenSutherlandClip(float,float,float,float);
    void bresenham_line(float,float,float,float);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int j,k;
    float x1,y1,x2,y2;
    float a[10][10];

    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

    // Defining x_max, y_max and x_min, y_min for
    // clipping rectangle. Since diagonal points are
    // enough to define a rectangle
    const int x_max = 350;
    const int y_max = 350;
    const int x_min = 50;
    const int y_min = 100;
};

#endif // MAINWINDOW_H
