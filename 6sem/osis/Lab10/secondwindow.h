#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QMouseEvent>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

public slots:
    void updateData(QString color, QString figure, bool is_avaliable);

private:
    QColor main_color = QColor("red");
    QString figure = "star";
    bool is_avaliable = false;
    QGraphicsScene* scene = new QGraphicsScene();
    Ui::SecondWindow *ui;
    void mousePressEvent(QMouseEvent *event);
};

#endif // SECONDWINDOW_H
