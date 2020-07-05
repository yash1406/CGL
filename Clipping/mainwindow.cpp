#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

QImage img(400,400,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    j = 0;
    k = 0;
    dda_line(50,100,350,100);
    dda_line(50,100,50,350);
    dda_line(50,350,350,350);
    dda_line(350,350,350,100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda_line(float x1, float y1, float x2, float y2)
{
    float dx,dy,len,x,y;
    float i = 0;

    dx = x2-x1;
    dy = y2-y1;

    if(abs(dx)>=abs(dy))
        len = abs(dx);
    else
        len = abs(dy);

    dx = dx/len;
    dy = dy/len;

    x = x1 + 0.5 * sign(x2-x1);
    y = y1 + 0.5 * sign(y2-y1);

    while (i<=len) {
        img.setPixel(x,y,qRgb(0,255,0));
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

float MainWindow::sign(float p)
{
    if(p<0)
        return -1;
    else
        return 1;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    if(k==0)
    {
        k++;
        x1 = a[j][0] = ev->pos().x();
        y1 = a[j][1] = ev->pos().y();
    }

    else if(k==1)
    {
        x2 = a[j][2] = ev->pos().x();
        y2 = a[j][3] = ev->pos().y();

        j++;
        k = 0;

        dda_line(x1,y1,x2,y2);
        ui->label->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_pushButton_clicked()
{
    cohenSutherlandClip(x1,y1,x2,y2);
}


// Function to compute region code for a point(x, y)
int MainWindow ::computeCode(float x, float y)
{
    // initialized as being inside
    int code = INSIDE;

    if (x < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (x > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (y < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (y > y_max)  // above the rectangle
        code |= TOP;

    return code;
}

// Implementing Cohen-Sutherland algorithm

void MainWindow :: cohenSutherlandClip(float cx1, float cy1, float cx2, float cy2)
{
    // Compute region codes for P1, P2
    int code1 = computeCode(cx1, cy1);
    int code2 = computeCode(cx2, cy2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Now intersection point x,y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        bresenham_line(x1,y1,x2,y2);
        // Here the user can add code to display the rectangle
        // along with the accepted (portion of) lines
    }
    else
    {}
}


void MainWindow::bresenham_line(float x1, float y1, float x2, float y2)
{
    float dx,dy,x,y,p;
    float i = 0;

    x = x1;
    y = y1;

    dx = abs(x2-x1);
    dy = abs(y2-y1);

    if(dx>=dy)
    {
        p = 2*dy-dx;

        while(i<dx)
        {
            img.setPixel(x,y,qRgb(255,255,255));

            if(p<0)
                p = p+2*dy;
            else
            {
                p = p+2*(dy-dx);
                y = y+sign(y2-y1);
            }

            x = x+sign(x2-x1);
            i++;
        }
    }
    else
    {
        p = 2*dx-dy;

        while(i<dy)
        {
            img.setPixel(x,y,qRgb(255,255,255));

            if(p<0)
                p = p+2*dx;
            else
            {
                p = p+2*(dx-dy);
                x = x+sign(x2-x1);
            }

            y = y+sign(y2-y1);
            i++;
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


