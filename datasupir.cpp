#include "datasupir.h"
#include "ui_datasupir.h"
#include <QMessageBox>

DataSupir::DataSupir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataSupir)
{
    ui->setupUi(this);

    // Initialize model for tableView
    model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({"ID", "Nama Supir", "NIK", "Alamat", "Harga Jaminan"});
    ui->tableView->setModel(model);

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &DataSupir::addData);
    connect(ui->updateButton, &QPushButton::clicked, this, &DataSupir::updateData);
    connect(ui->deleteButton, &QPushButton::clicked, this, &DataSupir::deleteData);
    connect(ui->sortButton, &QPushButton::clicked, this, &DataSupir::selectionSort);
}

DataSupir::~DataSupir()
{
    delete ui;
}

void DataSupir::addData()
{
    // Create a new Supir object and populate its fields
    Supir supir;
    supir.id = ui->idLineEdit->text();
    supir.namaSupir = ui->namaLineEdit->text();
    supir.nik = ui->nikLineEdit->text().toInt();
    supir.alamat = ui->alamatLineEdit->text();
    supir.hargaJaminan = ui->jaminanLineEdit->text().toDouble();

    // Add the Supir object to the list
    daftarSupir.append(supir);

    // Update the tableView
    perbaruiTampilanTableView();
}

void DataSupir::updateData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Retrieve updated data from line edits
    QString id = ui->idLineEdit->text();
    QString namaSupir = ui->namaLineEdit->text();
    int nik = ui->nikLineEdit->text().toInt();
    QString alamat = ui->alamatLineEdit->text();
    double hargaJaminan = ui->jaminanLineEdit->text().toDouble();

    // Update the selected row with the new data
    model->setData(model->index(row, 0), id);
    model->setData(model->index(row, 1), namaSupir);
    model->setData(model->index(row, 2), nik);
    model->setData(model->index(row, 3), alamat);
    model->setData(model->index(row, 4), hargaJaminan);

    // Clear line edits after updating data
    ui->idLineEdit->clear();
    ui->namaLineEdit->clear();
    ui->nikLineEdit->clear();
    ui->alamatLineEdit->clear();
    ui->jaminanLineEdit->clear();
}

void DataSupir::deleteData()
{
    // Retrieve selected row
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;

    int row = selectedIndexes.first().row();

    // Remove the Supir object from the list
    daftarSupir.removeAt(row);

    // Remove the selected row from the model
    model->removeRow(row);
}

void DataSupir::perbaruiTampilanTableView()
{
    // Clear the current content of the tableView
    model->removeRows(0, model->rowCount());

    // Fill the tableView with data from the list
    for (const Supir &supir : daftarSupir) {
        QList<QStandardItem *> row;
        row << new QStandardItem(supir.id)
            << new QStandardItem(supir.namaSupir)
            << new QStandardItem(QString::number(supir.nik))
            << new QStandardItem(supir.alamat)
            << new QStandardItem(QString::number(supir.hargaJaminan));
        model->appendRow(row);
    }
}

void DataSupir::selectionSort()
{
    int n = daftarSupir.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (daftarSupir[j].id.toInt() < daftarSupir[minIdx].id.toInt()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Swap the data positions
            std::swap(daftarSupir[i], daftarSupir[minIdx]);
        }
    }

    // Update the tableView after sorting
    perbaruiTampilanTableView();
}
