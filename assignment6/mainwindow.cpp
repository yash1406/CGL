#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
float ans[2][2]={0},pi=3.14;

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

    image.setPixel(cx+x,cy-y, value);
    while(i<=length)
    {

        x=x+dx;
        y=y+dy;
        image.setPixel(cx+int(x),cy-int(y),value);
        i++;
    }


    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2,w,h;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    dda(-150,0,150,0);
    dda(0,150,0,-150);

    dda(x1,y1,x2,y2);


}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2,w,h;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    w=ui->textEdit_5->toPlainText().toFloat();
    h=ui->textEdit_6->toPlainText().toFloat();
    value=qRgb(0,0,255);
    dda(x1+w,y1+h,x2+w,y2+h);


}



void MainWindow::transform(float mat[][2],float sx, float sy)
{

    int i=2,j=2,k=2;
    float temp[2][2]={0},a;
    temp[0][0]=sx;
    temp[1][1]=sy;

    if(sy==-1)
    {
        temp[0][0]=cos(sx*(pi/180));
        temp[0][1]=sin(sx*(pi/180));
        temp[1][0]=-sin(sx*(pi/180));
        temp[1][1]=cos(sx*(pi/180));

    }

    for(i=0;i<2;i++)
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

void MainWindow::on_pushButton_3_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[2][2]={0};
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    sx=ui->textEdit_7->toPlainText().toFloat();
    sy=ui->textEdit_8->toPlainText().toFloat();

     value=qRgb(0,255,0);
    mat[0][0]=x1;
    mat[0][1]=y1;
    mat[1][0]=x2;
    mat[1][1]=y2;


    transform(mat,sx,sy);
    dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);



}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[2][2]={0};
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    sx=ui->textEdit_9->toPlainText().toFloat();

    value=qRgb(255,0,0);

   mat[0][0]=x1;
   mat[0][1]=y1;
   mat[1][0]=x2;
   mat[1][1]=y2;

    transform(mat,sx,-1);
    dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);



}

void MainWindow::on_pushButton_5_clicked()
{
    float x1,y1,x2,y2,sx,sy,mat[2][2]={0},theta;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    sx=ui->textEdit_10->toPlainText().toFloat();
    sy=ui->textEdit_11->toPlainText().toFloat();
    theta=ui->textEdit_9->toPlainText().toFloat();

    mat[0][0]=x1;
    mat[0][1]=y1;
    mat[1][0]=x2;
    mat[1][1]=y2;


    value=qRgb(255,0,0);
    transform(mat,sx,sy);

    mat[0][0]=ans[0][0];
    mat[0][1]=ans[0][1];
    mat[1][0]=ans[1][0];
    mat[1][1]=ans[1][1];

    transform(mat,theta,-1);

dda(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);


}
