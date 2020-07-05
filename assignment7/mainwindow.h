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
    void bresenham(float x1,float y1,float x2,float y2);

private slots:
    void on_pushButton_clicked();
    int sign(float);
      void seedfill(int x,int y,QRgb);

      void transform(float mat[][2],float sx, float sy);

      void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
