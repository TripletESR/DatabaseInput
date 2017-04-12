#include "additemsdialog.h"
#include "ui_additemsdialog.h"

AddItemsDialog::AddItemsDialog(QString tableName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemsDialog)
{
    this->tableName = tableName;
    ui->setupUi(this);
}

AddItemsDialog::~AddItemsDialog()
{
    delete ui;
}

void AddItemsDialog::SetTableName(QString name)
{
    this->tableName = name;
}

void AddItemsDialog::SetPushButtonText(QString name)
{
    ui->pushButton_addItems->setText(name);
}

void AddItemsDialog::Setp1Name(QString name)
{
    ui->label_p1->setText(name);
    this->p1Name = name;
}

void AddItemsDialog::on_pushButton_addItems_clicked()
{
    QString name = "NAME";
    if( tableName == "Laser") name = "Name";
    QString str;
    str.sprintf("INSERT INTO %s (%s, %s) VALUES (:%s, :%s)",
                tableName.toStdString().c_str(),
                name.toStdString().c_str(),
                p1Name.toStdString().c_str(),
                name.toStdString().c_str(),
                p1Name.toStdString().c_str());
    QSqlQuery query;
    query.prepare(str);
    query.bindValue(0, ui->lineEdit_name->text());
    query.bindValue(1, ui->lineEdit_p1->text());
    query.exec();

    // ask the last entry to confirm
    str.sprintf("SELECT * FROM %s", tableName.toStdString().c_str());
    query.exec(str);
    int col = query.record().count();
    query.last();
    QString msg = "DB Written: ";
    for( int i = 0 ; i < col-1; i++){
        msg += query.value(i).toString() + ", ";
    }
    msg += query.value(col-1).toString();

    ClearEntries();
    //this->hide();
    ui->lineEdit_msg->setText(msg);
}

void AddItemsDialog::CheckDataComplete()
{
    if( !ui->lineEdit_name->text().isEmpty() && !ui->lineEdit_p1->text().isEmpty()){
        if( ui->lineEdit_p1->text().toDouble() != 0) {
            ui->pushButton_addItems->setEnabled(true);
        }else{
            ui->pushButton_addItems->setEnabled(false);
        }
    }else{
        ui->pushButton_addItems->setEnabled(false);
    }
}

void AddItemsDialog::ClearEntries()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_p1->clear();
    ui->lineEdit_msg->clear();
    ui->pushButton_addItems->setEnabled(false);
}

void AddItemsDialog::on_lineEdit_name_editingFinished()
{
    CheckDataComplete();
}

void AddItemsDialog::on_lineEdit_p1_editingFinished()
{
    CheckDataComplete();
}

void AddItemsDialog::on_lineEdit_p1_textChanged(const QString &arg1)
{
    CheckDataComplete();
}
