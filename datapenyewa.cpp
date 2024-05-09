#include "datapenyewa.h"
#include "ui_datapenyewa.h"
#include <QMessageBox>

DataPenyewa::DataPenyewa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataPenyewa)
{
    ui->setupUi(this);

    // Inisialisasi model untuk tableView
    model = new QStandardItemModel(0, 4, this);
    model->setHorizontalHeaderLabels({"ID", "Nama", "Durasi", "Pengemudi"});
    ui->tableView->setModel(model);

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &DataPenyewa::addData);
    connect(ui->updateButton, &QPushButton::clicked, this, &DataPenyewa::updateData);
    connect(ui->deleteButton, &QPushButton::clicked, this, &DataPenyewa::deleteData);
    connect(ui->sortButton, &QPushButton::clicked, this, &DataPenyewa::selectionSort);
}

DataPenyewa::~DataPenyewa()
{
    delete ui;
}

void DataPenyewa::addData()
{
    // Create a new Penyewa object and populate its fields
    Penyewa penyewa;
    penyewa.id = ui->idLineEdit->text();
    penyewa.nama = ui->namaLineEdit->text();
    penyewa.durasi = ui->durasiLineEdit->text();
    penyewa.pengemudi = ui->pengemudiLineEdit->text();

    // Menambahkan objek Penyewa ke dalam daftar
    daftarPenyewa.append(penyewa);

    // Memperbarui tampilan table view
    perbaruiTampilanTableView();
}

void DataPenyewa::updateData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Retrieve updated data from line edits
    QString id = ui->idLineEdit->text();
    QString nama = ui->namaLineEdit->text();
    QString durasi = ui->durasiLineEdit->text();
    QString pengemudi = ui->pengemudiLineEdit->text();

    // Update the selected row with the new data
    model->setData(model->index(row, 0), id);
    model->setData(model->index(row, 1), nama);
    model->setData(model->index(row, 2), durasi);
    model->setData(model->index(row, 3), pengemudi);

    // Clear line edits after updating data
    ui->idLineEdit->clear();
    ui->namaLineEdit->clear();
    ui->durasiLineEdit->clear();
    ui->pengemudiLineEdit->clear();
}

void DataPenyewa::deleteData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Hapus objek Penyewa dari daftar
    daftarPenyewa.removeAt(row);

    // Remove the selected row from the model
    model->removeRow(row);
}

void DataPenyewa::perbaruiTampilanTableView()
{
    // Menghapus konten saat ini dari table view
    model->removeRows(0, model->rowCount());

    // Mengisi table view dengan data dari daftar
    for (const Penyewa &penyewa : daftarPenyewa) {
        QList<QStandardItem *> baris;
        baris << new QStandardItem(penyewa.id)
              << new QStandardItem(penyewa.nama)
              << new QStandardItem(penyewa.durasi)
              << new QStandardItem(penyewa.pengemudi);
        model->appendRow(baris);
    }
}

void DataPenyewa::selectionSort()
{
    int n = daftarPenyewa.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (daftarPenyewa[j].id.toInt() < daftarPenyewa[minIdx].id.toInt()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Tukar posisi data
            std::swap(daftarPenyewa[i], daftarPenyewa[minIdx]);
        }
    }

    // Perbarui tampilan tabel setelah pengurutan
    perbaruiTampilanTableView();
}
