#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    if( QFile::exists(DB_PATH) ){
        qDebug() << "database exist : " << DB_PATH ;
    }else{
        qDebug() << "No database : " << DB_PATH ;
        return;
    }

    db.setDatabaseName(DB_PATH);
    db.open();
    if( !db.isOpen()){
        qDebug() << "Database open Error : " + DB_PATH ;
        return;
    }else{
        statusBar()->showMessage("Database openned. " + DB_PATH);
    }

    addChemical = new AddChemicalDialog(this);
    addSample = new AddSampleDialog(this);
}

MainWindow::~MainWindow()
{
    delete addChemical;
    delete addSample;
    delete ui;
}

void MainWindow::on_pushButton_addChemical_clicked()
{
    if( addChemical->isHidden()){
        addChemical->show();
    }
}

void MainWindow::on_pushButton_addSample_clicked()
{
    QSqlQuery query;
    query.exec("SELECT NAME FROM Chemical");

    QStringList chemicalList;
    chemicalList << "";
    while(query.next()){
        chemicalList << query.value(0).toString();
    }

    query.exec("SELECT NAME FROM Solvent");
    QStringList solventList;
    solventList << "";
    while(query.next()){
        solventList << query.value(0).toString();
    }

    addSample->AddChemicalList(chemicalList);
    addSample->AddSolventList(solventList);

    if( addSample->isHidden()){
        addSample->show();
    }
}
