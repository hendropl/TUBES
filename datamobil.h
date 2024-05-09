#ifndef DATAMOBIL_H
#define DATAMOBIL_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class DataMobil;
}

struct Mobil {
    QString id;
    QString namaMobil;
    QString jenisMobil;
    QString plat;
    double hargaSewa;
};

class DataMobil : public QDialog
{
    Q_OBJECT

public:
    explicit DataMobil(QWidget *parent = nullptr);
    ~DataMobil();

private slots:
    void addData();
    void updateData();
    void deleteData();
    void selectionSort();

private:
    Ui::DataMobil *ui;
    QStandardItemModel *model;
    QList<Mobil> daftarMobil;

    void perbaruiTampilanTableView();
};

#endif // DATAMOBIL_H
