#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "dialog1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SaveSetting();
    void LoadSetting();

private slots:
    void on_actionExit_triggered();

    void on_btnOpenDialog1_clicked();

    void on_pushButton_clicked();

    void serialPortRead();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
