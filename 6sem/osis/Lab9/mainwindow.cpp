#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    movie->start();
    movie->stop();
    ui->label->setMovie(movie);

    this->setWindowTitle("Crazy avocado");
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    movie->start();
    xEnd = event->x();
    yEnd = event->y();

    QPoint point = ui->label->pos();

    if (timer->isActive())
        timer->stop();

    timer->start(15);
}

void MainWindow::slotTimerAlarm()
{
    QPoint pos = ui->label->pos();

    int del_x = 5 * (xEnd - pos.rx() < 0 ? -1 : 1);
    int del_y = (5 * (yEnd - pos.ry() < 0 ? -1 : 1));

    ui->xLabel->setText(QString("Delta x: ") + QString::number(del_x));
    ui->yLabel->setText(QString("Delta y: ") + QString::number(del_y));


    if (abs(del_x) > abs(xEnd - pos.rx()))
        del_x = xEnd - pos.rx();

    if (abs(del_y) > abs(yEnd - pos.ry()))
        del_y = yEnd - pos.ry();

    if (del_x == 0 && del_y == 0)
    {
        timer->stop();
        movie->stop();
        return;
    }

    ui->label->move(pos.rx() + del_x, pos.ry() + del_y);
}
