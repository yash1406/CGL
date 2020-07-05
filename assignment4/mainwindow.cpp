#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMouseEvent"
#include"QColorDialog"

QImage image(300,300,QImage::Format_RGB888);

QRgb value=qRgb(0,255,0);



class QMouseEvent;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    start=true;
    j=0;

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

void MainWindow::mousePressEvent(QMouseEvent *ptr)
{
    int p,q;


    if(start==true)
    {
        p=ptr->pos().x();
        q=ptr->pos().y();
        a[j]=p;
        b[j]=q;
        if(ptr->button()==Qt::RightButton)
        {
            dda(a[0],b[0],a[j-1],b[j-1]);
            start=false;
        }

       else if(j>0)
        {
            dda(a[j],b[j],a[j-1],b[j-1]);
        }

        j++;
    }





}


void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float x,y,dx,dy,delx,dely,length,i=1;






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

    image.setPixel(x,y,value);
    while(i<=length)
    {

        x=x+dx;
        y=y+dy;image.setPixel(int(x),int(y),col.rgb());
        i++;
    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_clicked()
{
    col=QColorDialog::getColor();
}

