#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFile>
#include <QDebug>
#include "constant.h"
#include "addchemicaldialog.h"
#include "addsampledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_addChemical_clicked();

    void on_pushButton_addSample_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    AddChemicalDialog * addChemical;
    AddSampleDialog * addSample;
};

#endif // MAINWINDOW_H
