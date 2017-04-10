#ifndef ADDSAMPLEDIALOG_H
#define ADDSAMPLEDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMimeData>
#include <QFileDialog>
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

    void CheckDataComplete();

    void SetPicture(QLabel * label, QLineEdit *lineEdit, QString &sysPath, QString path);

private:
    Ui::AddSampleDialog *ui;

    QString picPath;
    QString spectrumPath;
};

#endif // ADDSAMPLEDIALOG_H
