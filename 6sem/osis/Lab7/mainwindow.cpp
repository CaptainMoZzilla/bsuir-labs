#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listView->setModel(model1);
    ui->listView_2->setModel(model2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButtom_clicked()
{
    QStringList list = model1->stringList();
    QString text = ui->textEdit->text();

    if (!list.contains(text)) {
        model1->insertRow(model1->rowCount());
        QModelIndex index = model1->index(model1->rowCount() - 1);
        model1->setData(index, ui->textEdit->text());
        ui->textEdit->clear();
    }
}

void MainWindow::on_moveRightButton_clicked()
{
    QStringList list = model2->stringList();
    QModelIndex index = ui->listView->currentIndex();
    QString text = model1->stringList().takeAt(index.row());

    if (!list.contains(text)) {
        model2->insertRow(model2->rowCount());
        QModelIndex index2 = model2->index(model2->rowCount() - 1);
        model2->setData(index2, text);
        model1->removeRow(index.row());
    }
}

void MainWindow::on_clearButton_clicked()
{
    model1->removeRows(0, model1->rowCount());
    model2->removeRows(0, model2->rowCount());
}

void MainWindow::on_deleteButton_clicked()
{
     model1->removeRow(ui->listView->currentIndex().row());
     model2->removeRow(ui->listView_2->currentIndex().row());
}
