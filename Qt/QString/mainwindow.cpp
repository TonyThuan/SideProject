#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString str1 = "Hello World";
    this->setWindowTitle(str1);

    QString str2 = QString(4,'T');
    qDebug() << str2;
    qDebug() << str1;
    cout << "Alo" << endl;
    qDebug() << str2.length();
    qDebug() << str1.size();

//    QString str3;
//    qDebug() << str3.isEmpty();
//    qDebug() << str2.isNull();

    qDebug() << str1.startsWith("Hello");
    qDebug() << str1.endsWith("ld");
    qDebug() << str1.contains("Wo");

    QString str4("Log In and Log Out");

    // Clear N chars in the end of string
    str4.chop(4);
    qDebug() << str4;

    // Clear chars in the end of string from Nth char
    str4.truncate(4);
    qDebug() << str4;

    QString str7("How ");
    QString str8("are YOU");

    qDebug() << str7.append(str8);
    QString str6(" ok");
    qDebug() << str6.prepend(str8);

    QString str5 = str1 + " " + str4;
    qDebug() << str5;

    str4.clear();
    qDebug() << str4;

    qDebug() << str6.toLower() << str6.toUpper() << str6;

    int i = 10;
    QString str9, str10, str11;
    // To string
    str9 = QString::number(i);
    qDebug() << str9 << str11.setNum(i) << i;
    // To hexa string
    str10 = QString::number(i, 16);
    qDebug() << str10;

    int day = 7;
    int month = 4;
    int year = 2024;
    QString str12 = QString("This day is %1/%2/%3").arg(day).arg(month).arg(year);
    qDebug() << str12;

    QString str = "2024";
    year = str.toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPlus_clicked()
{
    double x, y, res;
    x = ui->led1->text().toDouble();
    y = ui->led2->text().toDouble();

    res = x + y;

    ui->lblResult->setText(QString("Sum is: %1").arg(res));
}

