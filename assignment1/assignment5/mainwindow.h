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
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    bool start;
    int count,j;
    float a[20],b[20];
    void dda(float,float,float,float);
    int sign(float);
    QColor col;
    void seedfill(int x,int y,QRgb);

private slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
