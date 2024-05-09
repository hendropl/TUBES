#ifndef DATASUPIR_H
#define DATASUPIR_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class DataSupir;
}

struct Supir {
    QString id;
    QString namaSupir;
    int nik;
    QString alamat;
    double hargaJaminan;
};

class DataSupir : public QDialog
{
    Q_OBJECT

public:
    explicit DataSupir(QWidget *parent = nullptr);
    ~DataSupir();

private slots:
    void addData();
    void updateData();
    void deleteData();
    void selectionSort();

private:
    Ui::DataSupir *ui;
    QStandardItemModel *model;
    QList<Supir> daftarSupir;

    void perbaruiTampilanTableView();
};

#endif
