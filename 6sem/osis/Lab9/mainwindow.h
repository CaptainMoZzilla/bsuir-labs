#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <cmath>
#include <string>

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
    void slotTimerAlarm();
    void on_centralwidget_customContextMenuRequested(const QPoint &pos);

private:
    int xEnd, yEnd;
    QMovie *movie = new QMovie(":/data/image.gif");

    QTimer* timer = new QTimer();
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
