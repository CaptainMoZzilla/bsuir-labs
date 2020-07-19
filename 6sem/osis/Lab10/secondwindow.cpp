#include "secondwindow.h"
#include "ui_secondwindow.h"

#include <QDebug>


SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Second window");
    this->setFixedSize(QSize(400, 400));
    this->move(720, 200);

//    ui->graphicsView->sceneRect()
    ui->graphicsView->setScene(scene);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::mousePressEvent(QMouseEvent *event) {
    int x = event->x(), y = event->y();

    if (is_avaliable) {
        QAbstractGraphicsShapeItem *item;

       if (figure == "Square") {
            item = new QGraphicsRectItem(x, y, x - 5, x - 5);
        } else if (figure == "Circle") {
            item = new QGraphicsEllipseItem(x, y, x - 5, y - 5);
        } else if (figure == "Star") {
            QVector<QPointF> vec;
            vec << QPointF(x + 100, y + 50);
            for (int i = 1; i < 5; ++i)
                   vec << QPointF(x + (0.5 + 0.5 * std::cos(0.8 * i * 3.14)) * 100,
                                  y + (0.5 + 0.5 * std::sin(0.8 * i * 3.14)) * 100);

            item = new QGraphicsPolygonItem(QPolygonF(vec));

        } else {
           QVector<QPointF> vec;

//           vec << QPointF(x + 40, y + 50) << QPointF(x + 50, y + 40)
//               << QPointF(x + 60, y + 50) << QPointF(x + 50, y + 60)
//               << QPointF(x + 40, y + 50);
           vec << QPointF(x, y) << QPointF(x + 10, y - 10)
               << QPointF(x + 20, y) << QPointF(x + 10, y + 10)
               << QPointF(x, y);


           item = new QGraphicsPolygonItem(QPolygonF(vec));
       }

        item->setBrush(main_color);
        scene->addItem(item);
    }


}

void SecondWindow::updateData(QString color, QString figure, bool is_avaliable)
{
    main_color = QColor(color);
    this->is_avaliable = is_avaliable;
    this->figure = figure;
}
