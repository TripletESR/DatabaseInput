#ifndef ADDCHEMICALDIALOG_H
#define ADDCHEMICALDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QDropEvent>
#include <QMimeData>
#include "constant.h"

namespace Ui {
class AddChemicalDialog;
}

class AddChemicalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddChemicalDialog(QWidget *parent = 0);
    ~AddChemicalDialog();

private slots:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent * event);
    void on_pushButton_clicked();

    bool checkDataComplete();

    void on_lineEdit_name_editingFinished();

    void on_lineEdit_formula_editingFinished();

private:
    Ui::AddChemicalDialog *ui;

    QString picPath;
};

#endif // ADDCHEMICALDIALOG_H
