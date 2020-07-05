#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void dda(float,float,float,float);
    int sign(float a);


    void bresenham(float,float,float,float);

    void on_pushButton_2_clicked();
  //  QImage image(300,300,QImage::);

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
