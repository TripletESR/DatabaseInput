#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    if( QFile::exists(DB_PATH) ){
        msg = "database exist : " + DB_PATH;
        isDBOpened = true;
    }else{
        msg = "No database : " + DB_PATH;
        isDBOpened = false;
        //TODO created a db
        return;
    }
    db.setDatabaseName(DB_PATH);
    db.open();
    if( !db.isOpen()){
        msg = "Database open Error : " + DB_PATH;
        isDBOpened = false;
        return;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
