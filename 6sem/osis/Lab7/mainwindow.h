#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

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
    void on_pushButton_2_clicked();

    void on_addButtom_clicked();

    void on_moveRightButton_clicked();

    void on_clearButton_clicked();

    void on_deleteButton_clicked();

private:
    QStringListModel *model1 = new QStringListModel(this),
                     *model2 = new QStringListModel(this);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
