#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_Login_clicked()
{
    QString UserName = ui->lineEdit_User_Name->text();
    QString Password = ui->lineEdit_Password->text();
    if (UserName == "data sewa rental mobil" && Password == "kelompok 2")
    {
        QMessageBox::information(this, "Data Sewa Rental Mobil", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    else
    {
        QMessageBox::warning(this,"Data Sewa Rental Mobil","Please Enter Valid Username Or Password");
    }
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Data Sewa Rental Mobil","Are you sure to close the application?",QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

