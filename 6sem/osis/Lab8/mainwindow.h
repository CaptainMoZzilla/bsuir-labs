#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_drawButton_clicked();

    void on_clearButton_clicked();

private:
    QGraphicsScene* scene = new QGraphicsScene();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
