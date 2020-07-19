#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(QSize(520, 200));
    this->move(200, 200);

    ui->setupUi(this);
    secondWindow->show();

    ui->radioButton->setChecked(true);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_9->setChecked(true);

    for (auto & a : ui->colorBox->findChildren<QRadioButton *>())
        connect(a, &QRadioButton::toggled, this, &MainWindow::on_groupBox_toggled);

    for (auto & a : ui->figureBox->findChildren<QRadioButton *>())
        connect(a, &QRadioButton::toggled, this, &MainWindow::on_groupBox_toggled);

    for (auto & a : ui->drawBox->findChildren<QRadioButton *>())
        connect(a, &QRadioButton::toggled, this, &MainWindow::on_groupBox_toggled);

    connect(this, &MainWindow::send_data, secondWindow, &SecondWindow::updateData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_groupBox_toggled()
{
    QString color = get_togled_button_text(ui->colorBox);
    QString figure = get_togled_button_text(ui->figureBox);
    bool checker = ui->radioButton_8->isChecked();

    emit send_data(color, figure, checker);
}

QString MainWindow::get_togled_button_text(QGroupBox* box)
{
    for (auto & a : box->findChildren<QRadioButton *>()){
      if (a->isChecked()) {
        return a->text();
      }
    }
}
