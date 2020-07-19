#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    QCursor cursorTarget = QCursor(QPixmap(":/cursor/cursor_PNG50.png"));
    setCursor(cursorTarget);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    if (!ui->label->isVisible())
        ui->label->setVisible(true);

    if (!timer->isActive())
        timer->start(200);
}

void MainWindow::slotTimerAlarm()
{
    int del_x = (rand() % 2 ? - 1 : 1) * rand() % 10,
        del_y = (rand() % 2 ? - 1 : 1) * rand() % 10;

    int x = ui->label->x() + del_x,
        y = ui->label->y() + del_y;

    ui->label->move(x, y);
}

void MainWindow::on_actionStop_triggered()
{
    timer->stop();
}
