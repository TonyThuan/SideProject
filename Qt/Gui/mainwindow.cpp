#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->hsl, SIGNAL(valueChanged(int)), ui->prb, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbn_clicked()
{
    close();
}

void MainWindow::on_hsl_valueChanged(int value)
{
    ui->prb->setValue(value);
}

