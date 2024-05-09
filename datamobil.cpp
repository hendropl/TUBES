#include "datamobil.h"
#include "ui_datamobil.h"
#include <QMessageBox>

DataMobil::DataMobil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataMobil)
{
    ui->setupUi(this);

    // Inisialisasi model untuk tableView
    model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({"ID", "Nama Mobil", "Jenis Mobil", "Plat", "Harga Sewa"});
    ui->tableView->setModel(model);

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &DataMobil::addData);
    connect(ui->updateButton, &QPushButton::clicked, this, &DataMobil::updateData);
    connect(ui->deleteButton, &QPushButton::clicked, this, &DataMobil::deleteData);
    connect(ui->sortButton, &QPushButton::clicked, this, &DataMobil::selectionSort);
}


DataMobil::~DataMobil()
{
    delete ui;
}

void DataMobil::addData()
{
    // Create a new Mobil object and populate its fields
    Mobil mobil;
    mobil.id = ui->idLineEdit->text();
    mobil.namaMobil = ui->namaLineEdit->text();
    mobil.jenisMobil = ui->jenisLineEdit->text();
    mobil.plat = ui->platLineEdit->text();
    mobil.hargaSewa = ui->hargaLineEdit->text().toDouble();

    // Menambahkan objek Mobil ke dalam daftar
    daftarMobil.append(mobil);

    // Memperbarui tampilan table view
    perbaruiTampilanTableView();
}

void DataMobil::updateData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Retrieve updated data from line edits
    QString id = ui->idLineEdit->text();
    QString namaMobil = ui->namaLineEdit->text();
    QString jenisMobil = ui->jenisLineEdit->text();
    QString plat = ui->platLineEdit->text();
    QString hargaSewa = ui->hargaLineEdit->text();

    // Update the selected row with the new data
    model->setData(model->index(row, 0), id);
    model->setData(model->index(row, 1), namaMobil);
    model->setData(model->index(row, 2), jenisMobil);
    model->setData(model->index(row, 3), plat);
    model->setData(model->index(row, 4), hargaSewa);

    // Clear line edits after updating data
    ui->idLineEdit->clear();
    ui->namaLineEdit->clear();
    ui->jenisLineEdit->clear();
    ui->platLineEdit->clear();
    ui->hargaLineEdit->clear();
}

void DataMobil::deleteData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Hapus objek Mobil dari daftar
    daftarMobil.removeAt(row);

    // Remove the selected row from the model
    model->removeRow(row);
}

void DataMobil::perbaruiTampilanTableView()
{
    // Menghapus konten saat ini dari table view
    model->removeRows(0, model->rowCount());

    // Mengisi table view dengan data dari daftar
    for (const Mobil &mobil : daftarMobil) {
        QList<QStandardItem *> baris;
        baris << new QStandardItem(mobil.id)
              << new QStandardItem(mobil.namaMobil)
              << new QStandardItem(mobil.jenisMobil)
              << new QStandardItem(mobil.plat)
              << new QStandardItem(QString::number(mobil.hargaSewa));
        model->appendRow(baris);
    }
}

void DataMobil::selectionSort()
{
    int n = daftarMobil.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (daftarMobil[j].id.toInt() < daftarMobil[minIdx].id.toInt()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Tukar posisi data
            std::swap(daftarMobil[i], daftarMobil[minIdx]);
        }
    }

    // Perbarui tampilan tabel setelah pengurutan
    perbaruiTampilanTableView();
}
