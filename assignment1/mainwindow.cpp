#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(300,300,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2,w,h;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_3->toPlainText().toFloat();
    w=ui->textEdit_2->toPlainText().toFloat();
    h=ui->textEdit_4->toPlainText().toFloat();


   dda(x1,(2*y1+h)/2,(2*x1+w)/2,y1);
  // dda(x1,(2*y1+h)/2,(2*x1+w)/2,y1);
   dda((2*x1+w)/2,y1+h,x1+w,(2*y1+h)/2);
   dda((2*x1+w)/2,y1,x1+w,(2*y1+h)/2);
   dda(x1,(2*y1+h)/2,(2*x1+w)/2,y1+h);



}

int MainWindow::sign(float a)
{
    if(a>0)
        return 1;
    else if(a==0)
        return 0;
    return -1;
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2,w,h;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_3->toPlainText().toFloat();
    w=ui->textEdit_2->toPlainText().toFloat();
    h=ui->textEdit_4->toPlainText().toFloat();

    bresenham(x1,y1+h,x1+w,y1+h);
    bresenham(x1,y1,x1,y1+h);
    bresenham(x1+w,y1,x1+w,y1+h);
    bresenham(x1,y1,x1+w,y1);
   // bresenham(x1,y1+h,x1+w,y1+h);


   bresenham((4*x1+w)/4,(4*y1+h)/4,(4*x1+3*w)/4,(4*y1+h)/4);
   bresenham((4*x1+w)/4,(4*y1+h)/4,(4*x1+w)/4,(4*y1+3*h)/4);
   bresenham((4*x1+3*w)/4,(4*y1+h)/4,(4*x1+3*w)/4,(4*y1+3*h)/4);
   bresenham((4*x1+w)/4,(4*y1+3*h)/4,(4*x1+3*w)/4,(4*y1+3*h)/4);


}


void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float x,y,dx,dy;
    int delx,dely,length,i=1;


    QRgb value;
    value=qRgb(0,255,0);



    delx=abs(x2-x1);
    dely=abs(y2-y1);

    if(delx>dely)
        length=delx;
    else
        length=dely;

    dx=(x2-x1)/length;
    dy=(y2-y1)/length;

    x=x1+(0.5*sign(x2-x1));
    y=y1+(0.5*sign(y2-y1));

    image.setPixel(x1,y1,value);
    while(i<=length)
    {
        image.setPixel(int(x),int(y),value);
        x=x+dx;
        y=y+dy;
        i++;
    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::bresenham(float x1,float y1,float x2,float y2)
{
    int i,interchange;
    float e,dx,dy,temp,x,y;
    dx=abs(x2-x1);
    dy=abs(y2-y1);

    //QImage image(300,300,QImage::Format_RGB888);

    QRgb value;
    value=qRgb(0,255,0);

    if(dx>=dy)
        interchange=0;
    else
    {
        temp=dx;
        dx=dy;
        dy=temp;\

        interchange=1;
    }
    x=x1;
    y=y1;
    e=(2*dy)-dx;

    for(i=0;i<=dx;i++)
    {
        image.setPixel(x,y,value);
        while(e>=0)
        {
            if(interchange==1)
            {
                x=x+sign(x2-x1);
            }
            else
            {
                y=y+sign(y2-y1);
            }
            e=e-(2*dx);

        }
        if(interchange==1)
        {
            y=y+sign(y2-y1);
        }
        else
        {
            x=x+sign(x2-x1);
        }
        e=e+(2*dy);

    }


    ui->label->setPixmap(QPixmap::fromImage(image));


}

