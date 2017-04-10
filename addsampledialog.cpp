#include "addsampledialog.h"
#include "ui_addsampledialog.h"

AddSampleDialog::AddSampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSampleDialog)
{
    ui->setupUi(this);

    QDateTime date;

    ui->lineEdit_date->setText(date.currentDateTime().toString("yyyy-MM-dd"));

}

AddSampleDialog::~AddSampleDialog()
{
    delete ui;
}

void AddSampleDialog::AddChemicalList(QStringList list)
{
    ui->comboBox_chemical->addItems(list);
}

void AddSampleDialog::AddSolventList(QStringList list)
{
    ui->comboBox_solvent->addItems(list);
}
