#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "datasupir.h"
#include "datamobil.h"
#include "datapenyewa.h"

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
    DataSupir datasupir;
    DataMobil datamobil;
    DataPenyewa datapenyewa;

private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
