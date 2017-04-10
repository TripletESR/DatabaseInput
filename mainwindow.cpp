#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int configFileFlag  = loadConfigurationFile();

    if(configFileFlag == 1) {
        QMessageBox msgBox;
        msgBox.setText("The configuration file not exist.\n"
                       "please check the ProgramConfiguration.ini exist on Desktop.");
        msgBox.exec();
    }else if(configFileFlag == 2){
        QMessageBox msgBox;
        msgBox.setText("The configuration file fail to open.");
        msgBox.exec();
    }else if(configFileFlag == 3){
        QMessageBox msgBox;
        msgBox.setText("Some items are missing in configuration file.");
        msgBox.exec();
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    if( QFile::exists(DB_PATH) ){
        //qDebug() << "database exist : " << DB_PATH ;
    }else{
        //qDebug() << "No database : " << DB_PATH ;
        QMessageBox msgBox;
        msgBox.setText("Database failed to load.\n"+DB_PATH);
        msgBox.exec();
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

int MainWindow::loadConfigurationFile()
{
    QString path = DESKTOP_PATH + "/ProgramsConfiguration.ini";
    if( !QFile::exists(path) ){
        return 1;
    }

    QFile configFile(path);
    configFile.open(QIODevice::ReadOnly);
    if( !configFile.isOpen() ){
        return 2;
    }

    QTextStream stream(&configFile);
    QString line;
    QStringList lineList;

    int itemCount = 0;

    while(stream.readLineInto(&line) ){
        if( line.left(1) == "#" ) continue;
        lineList = line.split(" ");
        //qDebug() << lineList[0] << ", " << lineList[lineList.size()-1];
        if( lineList[0] == "DATA_PATH") {
            DATA_PATH = lineList[lineList.size()-1];
            itemCount ++;
        }
        if( lineList[0] == "DB_PATH") {
            DB_PATH = lineList[lineList.size()-1];
            itemCount ++;
        }
        if( lineList[0] == "ChemicalPicture_PATH") {
            CHEMICAL_PIC_PATH = lineList[lineList.size()-1];
            itemCount ++;
        }
        if( lineList[0] == "SamplePicture_PATH") {
            SAMPLE_PIC_PATH = lineList[lineList.size()-1];
            itemCount ++;
        }
    }

    if( itemCount != 4){
        return 3;
    }

    return 0;
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
