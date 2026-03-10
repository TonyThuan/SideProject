#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QtSerialPort>

QSerialPort *serialPort;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadSetting();

    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM1");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialPortRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
    serialPort->close();
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::SaveSetting()
{
    QSettings settings("ThuanDV", "Test Guide");
    settings.beginGroup("Save ui status");
    settings.setValue("Check box", ui->checkBox->isChecked());
    settings.endGroup();
}

void MainWindow::LoadSetting()
{
    QSettings settings("ThuanDV", "Test Guide");
    settings.beginGroup("Save ui status");
    ui->checkBox->setChecked(settings.value("Check box").toBool());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveSetting();
}


void MainWindow::on_btnOpenDialog1_clicked()
{
    Dialog1 cDialog(this);
    cDialog.setModal(true);
    cDialog.exec();
}


void MainWindow::on_pushButton_clicked()
{
    serialPort->write(ui->ledSend->text().toStdString().data());
}

void MainWindow::serialPortRead()
{
    ui->pteReceive->moveCursor(QTextCursor::End);
    ui->pteReceive->insertPlainText(serialPort->readAll());
}

