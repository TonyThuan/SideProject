#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnInfo_clicked()
{
    QMessageBox::information(this, "Info", "Hello buddy");
}

void MainWindow::on_btnQues_clicked()
{
    if(QMessageBox::question(this, "Question", "Do you want to exit", QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Yes)
        this->close();
}


void MainWindow::on_btnWarn_clicked()
{
    QMessageBox::warning(this, "Warning", "This is a warning");
}


void MainWindow::on_btnCri_clicked()
{
    QMessageBox::critical(this, "Critical", "This is a critical");
}

