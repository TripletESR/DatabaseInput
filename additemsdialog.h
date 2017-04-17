#ifndef ADDITEMSDIALOG_H
#define ADDITEMSDIALOG_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class AddItemsDialog;
}

class AddItemsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemsDialog(QString tableName, QWidget *parent = 0);
    ~AddItemsDialog();

    void SetTableName(QString name);
    void SetPushButtonText(QString name);
    void Setp1Name(QString name);
    void ClearEntries();

private slots:
    void on_pushButton_addItems_clicked();

    void CheckDataComplete();

    void on_lineEdit_name_editingFinished();
    void on_lineEdit_p1_editingFinished();

    void on_lineEdit_p1_textChanged(const QString &arg1);

private:
    Ui::AddItemsDialog *ui;

    QString tableName;
    QString p1Name;
};

#endif // ADDITEMSDIALOG_H
