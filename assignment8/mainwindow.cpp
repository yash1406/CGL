#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
float ans[4][2]={0},pi=3.14;


QImage image(301,301,QImage::Format_RGB888);
QRgb value=qRgb(0,255,0);



int cx=150,cy=150;



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
    float x,y,dx,dy, delx,dely,length,i=1;


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

    image.setPixel(cx+(int)x,cy-(int)y,value);
    while(i<=length)
    {

        x=x+dx;
        y=y+dy;
        image.setPixel(cx+(int)x,cy-(int)y,value);
        i++;
    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::transform(float mat[][2],float sx, float sy)
{

    int i=2,j=2,k=2;
    float temp[2][2]={0},a;
    temp[0][1]=0;
    temp[1][0]=0;

    if(sy==0 && sx==0)
    {
        temp[0][0]=-1;

        temp[1][1]=1;

    }
    if(sx==1 && sy==0)
    {
        temp[0][0]=1;

        temp[1][1]=-1;

    }
    if(sx==0 && sy==1)
    {
        temp[0][0]=0;
        temp[0][1]=1;
        temp[1][0]=1;

        temp[1][1]=0;

    }

    for(i=0;i<4;i++)
    {
        for(j=0;j<2;j++)
        {
            a=0;
            for(k=0;k<2;k++)
            {
               a+=((mat[i][k])*(temp[k][j]));
            }
            ans[i][j]=a;
        }
    }



}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[4][2]={0},x3,y3,x4,y4;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    x3=ui->textEdit_5->toPlainText().toFloat();
    y3=ui->textEdit_6->toPlainText().toFloat();
    x4=ui->textEdit_7->toPlainText().toFloat();
    y4=ui->textEdit_8->toPlainText().toFloat();


    value=qRgb(255,255,255);

   mat[0][0]=x1;
   mat[0][1]=y1;
   mat[1][0]=x2;
   mat[1][1]=y2;

   mat[2][0]=x3;
   mat[2][1]=y3;
   mat[3][0]=x4;
   mat[3][1]=y4;



    transform(mat,0,0);
    dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
    dda(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
    dda(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
    dda(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);


    ui->label->setPixmap(QPixmap::fromImage(image));



}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[4][2]={0},x3,y3,x4,y4;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    x3=ui->textEdit_5->toPlainText().toFloat();
    y3=ui->textEdit_6->toPlainText().toFloat();
    x4=ui->textEdit_7->toPlainText().toFloat();
    y4=ui->textEdit_8->toPlainText().toFloat();


    value=qRgb(255,0,0);

   mat[0][0]=x1;
   mat[0][1]=y1;
   mat[1][0]=x2;
   mat[1][1]=y2;

   mat[2][0]=x3;
   mat[2][1]=y3;
   mat[3][0]=x4;
   mat[3][1]=y4;


   transform(mat,1,0);
   dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
   dda(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
   dda(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
   dda(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);

   ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_3_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[4][2]={0},x3,y3,x4,y4;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    x3=ui->textEdit_5->toPlainText().toFloat();
    y3=ui->textEdit_6->toPlainText().toFloat();
    x4=ui->textEdit_7->toPlainText().toFloat();
    y4=ui->textEdit_8->toPlainText().toFloat();


    value=qRgb(0,255,0);

   mat[0][0]=x1;
   mat[0][1]=y1;
   mat[1][0]=x2;
   mat[1][1]=y2;

   mat[2][0]=x3;
   mat[2][1]=y3;
   mat[3][0]=x4;
   mat[3][1]=y4;


   transform(mat,0,1);
   dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
   dda(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
   dda(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
   dda(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);

   ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[4][2]={0},x3,y3,x4,y4;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    x3=ui->textEdit_5->toPlainText().toFloat();
    y3=ui->textEdit_6->toPlainText().toFloat();
    x4=ui->textEdit_7->toPlainText().toFloat();
    y4=ui->textEdit_8->toPlainText().toFloat();


    value=qRgb(0,0,255);

   mat[0][0]=x1;
   mat[0][1]=y1;
   mat[1][0]=x2;
   mat[1][1]=y2;

   mat[2][0]=x3;
   mat[2][1]=y3;
   mat[3][0]=x4;
   mat[3][1]=y4;

   dda(-150,0,150,0);
   dda(0,150,0,-150);

   dda(mat[0][0],mat[0][1],mat[1][0],mat[1][1]);
   dda(mat[1][0],mat[1][1],mat[2][0],mat[2][1]);
   dda(mat[2][0],mat[2][1],mat[3][0],mat[3][1]);
   dda(mat[3][0],mat[3][1],mat[0][0],mat[0][1]);
   ui->label->setPixmap(QPixmap::fromImage(image));

}
