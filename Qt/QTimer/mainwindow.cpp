#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

QTimer *timer;
int cnt = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
//    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);
}

void MainWindow::timerTimeout()
{
    if(cnt < 0)
    {
        delete timer;
        this->close();
    }
    ui->lblCounter->setText(QString::number(cnt));
    cnt--;
}

MainWindow::~MainWindow()
{
    delete ui;
}

