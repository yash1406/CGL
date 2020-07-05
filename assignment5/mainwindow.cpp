#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMouseEvent"
#include"QColorDialog"

QImage image(300,300,QImage::Format_RGB888);

QRgb value=qRgb(0,255,0),current,newcolor=qRgb(0,255,0);


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

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ptr)
{
    int p,q;
    p=ptr->pos().x();
    q=ptr->pos().y();
    seedfill(p,q,newcolor);
    ui->label->setPixmap(QPixmap::fromImage(image));
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
            //current=image.pixel(p,q);
            //seedfill(p,q,newcolor);
            //ui->label->setPixmap(QPixmap::fromImage(image));
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
    float x,y,dx,dy, delx,dely,length,i=1;


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

    image.setPixel(x,y,col.rgb());
    while(i<=length)
    {

        x=x+dx;
        y=y+dy; image.setPixel(int(x),int(y),col.rgb());
        i++;
    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::on_pushButton_clicked()
{
    col=QColorDialog::getColor();
    newcolor=value;

}

void MainWindow::seedfill(int x, int y,QRgb newcolor)
{


    if(image.pixel(x,y)!=newcolor && image.pixel(x,y)!=col.rgb())
    {
        image.setPixel(x,y,newcolor);
        seedfill(x+1,y,newcolor);
        seedfill(x-1,y,newcolor);
        seedfill(x,y+1,newcolor);
        seedfill(x,y-1,newcolor);

    }
}


