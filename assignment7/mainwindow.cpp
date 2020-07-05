#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

QImage image(301,301,QImage::Format_RGB888);
QImage tempimage(301,301,QImage::Format_RGB888);

QRgb value=qRgb(255,255,255),current,newcolor=qRgb(255,255,255);
float ans[16][2]={0},pi=3.14;
int cx=150,cy=150,temp=0;

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


void MainWindow::bresenham(float x1,float y1,float x2,float y2)
{
    int i,interchange;
    float e,dx,dy,temp,x,y;
    dx=abs(x2-x1);
    dy=abs(y2-y1);



    QRgb value;
    value=qRgb(255,255,255);

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


    ui->label_4->setPixmap(QPixmap::fromImage(image));


}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2,w,h,mat[16][2],x,y;
    int i,j;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    w=ui->textEdit_3->toPlainText().toFloat();




    mat[0][0]=x1; mat[0][1]=y1;
    mat[1][0]=x1+(w/4); mat[1][1]=y1;
    mat[2][0]=x1+(w/2); mat[2][1]=y1;
    mat[3][0]=x1+(3*w/4); mat[3][1]=y1;
    mat[4][0]=x1+w; mat[4][1]=y1;
    mat[5][0]=x1; mat[5][1]=y1+w;
    mat[6][0]=x1+(w/4); mat[6][1]=y1+w;
    mat[7][0]=x1+(w/2); mat[7][1]=y1+w;
    mat[8][0]=x1+(3*w/4); mat[8][1]=y1+w;
    mat[9][0]=x1+w; mat[9][1]=y1+w;

    mat[10][0]=x1; mat[10][1]=y1+(w/4);
    mat[11][0]=x1; mat[11][1]=y1+(w/2);
    mat[12][0]=x1; mat[12][1]=y1+(3*w/4);
    mat[13][0]=x1+w; mat[13][1]=y1+(w/4);
    mat[14][0]=x1+w; mat[14][1]=y1+(w/2);
    mat[15][0]=x1+w; mat[15][1]=y1+(3*w/4);


    for(i=0;i<16;i++)
    {
        mat[i][0]+=-x1;
        mat[i][1]+=-y1;

    }

 transform(mat,-1,-1);


 for(i=0;i<16;i++)
 {
     ans[i][0]+=x1;
     ans[i][1]+=y1;

 }



 image=tempimage;


    for(i=0;i<5;i++)
     {
         bresenham(  ans[i][0],ans[i][1],ans[i+5][0],ans[i+5][1]);
     }
     for(i=10;i<=12;i++)
     {
         bresenham(  ans[i][0],ans[i][1],ans[i+3][0],ans[i+3][1]);

     }
     bresenham(  ans[0][0],ans[0][1],ans[4][0],ans[4][1]);
     bresenham(  ans[5][0],ans[5][1],ans[9][0],ans[9][1]);

    newcolor==qRgb(255,255,255);



     seedfill(ans[0][0],ans[0][1]+2,newcolor);
     seedfill(ans[2][0],ans[2][1]+2,newcolor);
     seedfill(ans[6][0]+2,ans[6][1],newcolor);
     seedfill(ans[8][0]+2,ans[8][1],newcolor);

     seedfill(ans[12][0]+2,ans[12][1],newcolor);
     seedfill(ans[14][0],ans[14][1]-2,newcolor);

    x=(ans[11][0]+ans[14][0])/2;
    y=(ans[11][1]+ans[14][1])/2;


     seedfill(x,y+2,newcolor);
     seedfill(x,y-2,newcolor);

     ui->label_4->setPixmap(QPixmap::fromImage(image));


}

void MainWindow::transform(float mat[][2],float sx, float sy)
{

    int i=2,j=2,k=2;
    float temp[2][2]={0},a;
    temp[0][0]=sx;
    temp[1][1]=sy;

    if(sy==-1)
    {
        temp[0][0]=cos(45*(pi/180));
        temp[0][1]=sin(45*(pi/180));
        temp[1][0]=-sin(45*(pi/180));
        temp[1][1]=cos(45*(pi/180));

    }

    for(i=0;i<16;i++)
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


void MainWindow::seedfill(int x, int y,QRgb newcolor)
{


    if(image.pixel(x,y)!=newcolor && image.pixel(x,y)!=value)
    {
        image.setPixel(x,y,newcolor);

        seedfill(x+1,y,newcolor);
        seedfill(x-1,y,newcolor);
        seedfill(x,y+1,newcolor);
        seedfill(x,y-1,newcolor);

    }
}



void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2,w,h,mat[16][2],x,y;
    int i,j;
    temp=1;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    w=ui->textEdit_3->toPlainText().toFloat();


    mat[0][0]=x1; mat[0][1]=y1;
    mat[1][0]=x1+(w/4); mat[1][1]=y1;
    mat[2][0]=x1+(w/2); mat[2][1]=y1;
    mat[3][0]=x1+(3*w/4); mat[3][1]=y1;
    mat[4][0]=x1+w; mat[4][1]=y1;
    mat[5][0]=x1; mat[5][1]=y1+w;
    mat[6][0]=x1+(w/4); mat[6][1]=y1+w;
    mat[7][0]=x1+(w/2); mat[7][1]=y1+w;
    mat[8][0]=x1+(3*w/4); mat[8][1]=y1+w;
    mat[9][0]=x1+w; mat[9][1]=y1+w;

    mat[10][0]=x1; mat[10][1]=y1+(w/4);
    mat[11][0]=x1; mat[11][1]=y1+(w/2);
    mat[12][0]=x1; mat[12][1]=y1+(3*w/4);
    mat[13][0]=x1+w; mat[13][1]=y1+(w/4);
    mat[14][0]=x1+w; mat[14][1]=y1+(w/2);
    mat[15][0]=x1+w; mat[15][1]=y1+(3*w/4);



    for(i=0;i<5;i++)
     {
         bresenham(  mat[i][0],mat[i][1],mat[i+5][0],mat[i+5][1]);
     }
     for(i=10;i<=12;i++)
     {
         bresenham(  mat[i][0],mat[i][1],mat[i+3][0],mat[i+3][1]);

     }
     bresenham(  mat[0][0],mat[0][1],mat[4][0],mat[4][1]);
     bresenham(  mat[5][0],mat[5][1],mat[9][0],mat[9][1]);


     newcolor==qRgb(255,255,255);

     seedfill(mat[0][0]+2,mat[0][1]+2,newcolor);
     seedfill(mat[2][0]+2,mat[2][1]+2,newcolor);
     seedfill(mat[6][0]+2,mat[6][1]-2,newcolor);
     seedfill(mat[8][0]+2,mat[8][1]-2,newcolor);

     seedfill(mat[12][0]+2,mat[12][1]-2,newcolor);
     seedfill(mat[14][0]-2,mat[14][1]-2,newcolor);

    x=(mat[11][0]+mat[14][0])/2;
    y=(mat[11][1]+mat[14][1])/2;


     seedfill(x+2,y+2,newcolor);
     seedfill(x-2,y-2,newcolor);

     ui->label_4->setPixmap(QPixmap::fromImage(image));


}
