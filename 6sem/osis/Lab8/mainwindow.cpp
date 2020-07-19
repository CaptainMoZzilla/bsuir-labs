#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSize buttonSize= QSize(128, 128);

    ui->drawButton->setIconSize(buttonSize);
    ui->clearButton->setIconSize(buttonSize);

    ui->drawButton->setFixedSize(buttonSize);
    ui->clearButton->setFixedSize(buttonSize);
    ui->graphicsView->setScene(scene);

    //scene->setSceneRect(size.width(), size.height(), size.rwidth(), size.rheight());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_drawButton_clicked()
{
    int mod = 150;

    for (int a = 0; a < 20; a++)
    {
        int xStart = rand() % mod,
            yStart = rand() % mod,
            xEnd = (xStart + rand() % (mod / 6)) * (rand() % 2 ? 1 : -1),
            yEnd = (xStart + rand() % (mod / 6)) * (rand() % 2 ? 1 : -1);

        switch (rand() % 4) {
            case 0:
                scene->addItem(new QGraphicsRectItem(xStart, yStart, xEnd, yEnd));
                break;
            case 1:
                scene->addItem(new QGraphicsLineItem(xStart, yStart, xEnd, yEnd));
                break;
            case 2:
                scene->addItem(new QGraphicsEllipseItem(xStart, yStart, xEnd, yEnd));
                break;
            case 3:
                QPolygonF polygon = QPolygonF(QVector<QPointF>() << QPointF(xStart, xStart) << QPointF(xEnd, xEnd)
                                            << QPointF(yStart, yStart) << QPointF(yEnd, yEnd)
                                            << QPointF(rand() % 100, rand() % 100));
                scene->addItem(new QGraphicsPolygonItem(polygon));
                break;
        }
    }
}

void MainWindow::on_clearButton_clicked()
{
    scene->clear();
    ui->graphicsView->setScene(nullptr);
    ui->graphicsView->setScene(scene);
}
