#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
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

int MainWindow::sign(float a)
{
    if(a>0)
        return 1;
    else if(a==0)
        return 0;
    return -1;
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

void MainWindow::on_pushButton_clicked()
{

        float x1,y1,r;
        x1=ui->textEdit->toPlainText().toFloat();
        r=ui->textEdit_3->toPlainText().toFloat();
        y1=ui->textEdit_2->toPlainText().toFloat();

        ddar(x1,y1,r/2);


}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,r;
    x1=ui->textEdit->toPlainText().toFloat();
    r=ui->textEdit_3->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();

    bresenhamre(x1,y1,r);

}

void MainWindow::on_pushButton_3_clicked()
{
    float x,y,r,temp;
    x=ui->textEdit->toPlainText().toFloat();
    r=ui->textEdit_3->toPlainText().toFloat();
    y=ui->textEdit_2->toPlainText().toFloat();

    temp=(sqrt(3)*r)/2;
    dda(x,y-r,x-temp,y+(r/2));

    dda(x,y-r,x+temp,y+(r/2));

    dda(x-temp,y+(r/2),x+temp,y+(r/2));

}


void MainWindow::ddar(float x,float y,float r)
{
    float st_x,st_y,e,x1,y1,x2,y2;
    int i=0,val;

    QRgb value;
    value=qRgb(0,255,0);


    st_x=r;
    st_y=0;
    x1=st_x;
    y1=st_y;

    do
    {
        val=pow(2,i);
        i++;
    }while(val<r);
    e=1/pow(2,i-1);

    do
    {
        x2=x1+(e*y1);
        y2=y1-(e*x2);
        image.setPixel(x+x2,y+y2,value);
        x1=x2;
        y1=y2;



    }while((y1-st_y < e) || (st_x-x1) > e);


    ui->label->setPixmap(QPixmap::fromImage(image));


}


void MainWindow::bresenhamr(int x1,int y1,int r)
{
    int del1,del2,d,x,y,limit=0;
        x=0;
        y=r;
        d=2*(1-r);
        QRgb value;
        value=qRgb(0,255,0);

        while(y>=limit)
        {
            image.setPixel(x+x1,y+y1,value);
            image.setPixel(-x+x1,-y+y1,value);
            image.setPixel(x+x1,-y+y1,value);
            image.setPixel(-x+x1,y+y1,value);


            if(d<0)
            {
                del2=(2*d)+(2*y)-1;
                if(del2 <= 0)
                {
                    x=x+1;
                    d=d+(2*x)+1;
                }
                else
                {
                    x=x+1;
                    y=y-1;
                    d=d+(2*x)-(2*y)+2;
                }
            }
            else if(d>0)
            {
                del1=(2*d)-(2*x)-1;
                if(del1 > 0)
                {
                    y=y-1;
                    d=d-(2*y)+1;
                }
                else
                {
                    x=x+1;
                    y=y-1;
                    d=d+(2*x)-(2*y)+2;

                }
            }
            else
            {
                x=x+1;
                y=y-1;
                d=d+(2*x)-(2*y)+2;

            }

        }
        ui->label->setPixmap(QPixmap::fromImage(image));


}

void MainWindow::bresenhamre(int x1,int y1,int r)
{

    float e;
    int x,y;

    QRgb value;
    value=qRgb(0,255,0);

    x=0;
    y=r;
    e=3-(2*r);

    while(x<=y)
    {
        if(e<=0)
        {
            e+=4*x+6;
        }
        else
        {
            e+=4*(x-y)+10;
            y--;
        }
        x++;
        image.setPixel(x+x1,y+y1,value);
        image.setPixel(x+x1,-y+y1,value);
        image.setPixel(-x+x1,-y+y1,value);
        image.setPixel(-x+x1,y+y1,value);

        image.setPixel(y+x1,x+y1,value);
        image.setPixel(y+x1,-x+y1,value);
        image.setPixel(-y+x1,-x+y1,value);
        image.setPixel(-y+x1,x+y1,value);

    }


    ui->label->setPixmap(QPixmap::fromImage(image));


}



