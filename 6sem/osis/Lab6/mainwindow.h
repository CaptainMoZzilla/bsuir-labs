#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void on_actionStart_triggered();

    void on_actionStop_triggered();

private:
    QTimer *timer;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
