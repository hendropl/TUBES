#include "mainpage.h"
#include "datasupir.h"
#include "datapenyewa.h"
#include "datamobil.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_pushButton_clicked()
{
    datasupir.show();
}


void MainPage::on_pushButton2_clicked()
{
    datamobil.show();
}


void MainPage::on_pushButton3_clicked()
{
    datapenyewa.show();
}
