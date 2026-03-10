#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnHello, SIGNAL(clicked()), this, SLOT(displayText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayText()
{
    ui->lblText1->setText("Hello bro");
}

