#include "mainwindow.h"
#include "ui_mainwindow.h"


QImage image(300,300,QImage::Format_RGB888);
int b;
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


void MainWindow::dda(float x1,float y1,float x2,float y2,int dash,int dot,int gap)
{
    float x,y,dx,dy,temp,a1,a2;
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
    if(gap!=-1)
    {
        image.setPixel(x1,y1,value);

    }

    while(i<=length)
    {
        if(b==-1)
        {
            image.setPixel(int(x),int(y),value);

        }

        if(dash==1 && gap%20<=10)
        {
            image.setPixel(int(x),int(y),value);

        }
        if(dot==1 && gap%5==0)
        {
            image.setPixel(int(x),int(y),value);

        }
        if(dash==0 && dot==0)
        {
            image.setPixel(int(x),int(y),value);

        }
        if(dash==1 && dot==1 && (gap%20<=5 || gap%5==0))
        {
            image.setPixel(int(x),int(y),value);

        }


        x=x+dx;
        y=y+dy;
        i++;
        gap++;

    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit_6->toPlainText().toFloat();
    y1=ui->textEdit_7->toPlainText().toFloat();
    x2=ui->textEdit_8->toPlainText().toFloat();
    y2=ui->textEdit_9->toPlainText().toFloat();


    dda(x1,y1,x2,y2,0,0,0);


}

void MainWindow::on_pushButton_3_clicked()
{

    float x1,y1,x2,y2,width;
    x1=ui->textEdit_6->toPlainText().toFloat();
    y1=ui->textEdit_7->toPlainText().toFloat();
    x2=ui->textEdit_8->toPlainText().toFloat();
    y2=ui->textEdit_9->toPlainText().toFloat();
    width=ui->textEdit->toPlainText().toFloat();

    dda(x1,y1,x2,y2,1,0,width);

}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2,width;
    x1=ui->textEdit_6->toPlainText().toFloat();
    y1=ui->textEdit_7->toPlainText().toFloat();
    x2=ui->textEdit_8->toPlainText().toFloat();
    y2=ui->textEdit_9->toPlainText().toFloat();
    width=ui->textEdit->toPlainText().toFloat();

    dda(x1,y1,x2,y2,0,1,width);

}

void MainWindow::on_pushButton_5_clicked()
{
    float x1,y1,x2,y2,width;
    x1=ui->textEdit_6->toPlainText().toFloat();
    y1=ui->textEdit_7->toPlainText().toFloat();
    x2=ui->textEdit_8->toPlainText().toFloat();
    y2=ui->textEdit_9->toPlainText().toFloat();
    width=ui->textEdit->toPlainText().toFloat();

    dda(x1,y1,x2,y2,1,1,width);

}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2,width;
    x1=ui->textEdit_6->toPlainText().toFloat();
    y1=ui->textEdit_7->toPlainText().toFloat();
    x2=ui->textEdit_8->toPlainText().toFloat();
    y2=ui->textEdit_9->toPlainText().toFloat();
    width=ui->textEdit->toPlainText().toFloat();
    b=1;
    while(width--)
    {

        dda(x1,y1,x2,y2,0,0,-1);
        dda(x1,y1-1,x2,y2-1,0,0,-1);
        dda(x1,y1+1,x2,y2+1,0,0,-1);

    }
}
