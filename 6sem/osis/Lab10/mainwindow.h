#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QMainWindow>
#include "secondwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
void send_data(QString color, QString figure, bool is_avaliable);

private slots:
void on_groupBox_toggled();
void on_colorBox_clicked();

private:
    SecondWindow *secondWindow = new SecondWindow();
    Ui::MainWindow *ui;
    QString get_togled_button_text(QGroupBox* box);
};

#endif // MAINWINDOW_H
