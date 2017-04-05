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
        statusBar()->showMessage("Database openned. ");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
