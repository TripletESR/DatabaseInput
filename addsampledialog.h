#ifndef ADDSAMPLEDIALOG_H
#define ADDSAMPLEDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMimeData>
#include <QFileDialog>
#include <QtSql>
#include <QLabel>
#include <QLineEdit>
#include "constant.h"

namespace Ui {
class AddSampleDialog;
}

class AddSampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSampleDialog(QWidget *parent = 0);
    ~AddSampleDialog();

    void dragEnterEvent(QDragEnterEvent * event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent * event);
    void mousePressEvent(QMouseEvent * mouse);

    void AddChemicalList(QStringList list);
    void AddSolventList(QStringList list);
    void ClearEntries();

private slots:

    void CheckDataComplete();
    void SetPicture(QLabel * label, QLineEdit *lineEdit, QString &sysPath, QString path);

    void on_lineEdit_sampleName_editingFinished();
    void on_lineEdit_concentration_editingFinished();
    void on_lineEdit_maker_editingFinished();
    void on_comboBox_chemical_currentIndexChanged(int index);
    void on_comboBox_solvent_currentIndexChanged(int index);
    void on_pushButton_clicked();


private:
    Ui::AddSampleDialog *ui;

    QString picPath;
    QString spectrumPath;
};

#endif // ADDSAMPLEDIALOG_H
