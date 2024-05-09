#ifndef DATAPENYEWA_H
#define DATAPENYEWA_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class DataPenyewa;
}

struct Penyewa {
    QString id;
    QString nama;
    QString durasi;
    QString pengemudi;
};

class DataPenyewa : public QDialog
{
    Q_OBJECT

public:
    explicit DataPenyewa(QWidget *parent = nullptr);
    ~DataPenyewa();

private slots:
    void addData();
    void updateData();
    void deleteData();
    void selectionSort();

private:
    Ui::DataPenyewa *ui;
    QStandardItemModel *model;
    QList<Penyewa> daftarPenyewa;

    void perbaruiTampilanTableView();
};

#endif
