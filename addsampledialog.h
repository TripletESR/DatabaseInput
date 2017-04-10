#ifndef ADDSAMPLEDIALOG_H
#define ADDSAMPLEDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class AddSampleDialog;
}

class AddSampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSampleDialog(QWidget *parent = 0);
    ~AddSampleDialog();

    void AddChemicalList(QStringList list);
    void AddSolventList(QStringList list);

private:
    Ui::AddSampleDialog *ui;
};

#endif // ADDSAMPLEDIALOG_H
