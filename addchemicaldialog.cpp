#include "addchemicaldialog.h"
#include "ui_addchemicaldialog.h"

AddChemicalDialog::AddChemicalDialog( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddChemicalDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}

AddChemicalDialog::~AddChemicalDialog()
{
    delete ui;
}

void AddChemicalDialog::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void AddChemicalDialog::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void AddChemicalDialog::dropEvent(QDropEvent *event)
{
    const QMimeData * mimeData = event->mimeData();

    picPath = mimeData->urls().at(0).toLocalFile();

    QImage image(picPath);
    int imageH = image.height();
    int imageW = image.width();

    int labelH = ui->label->geometry().height();
    int labelW = ui->label->geometry().width();

    QImage scaledImage;
    if( 1.*imageH/imageW > 1.*labelH/labelW){
        scaledImage = image.scaledToHeight(labelH);
    }else{
        scaledImage = image.scaledToWidth(labelW);
    }
    //ui->label->resize(image.width(), image.height());
    ui->label->setPixmap( QPixmap::fromImage( scaledImage) );

    ui->lineEdit_picPath->setText(picPath);

    checkDataComplete();

}

void AddChemicalDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Chemical (NAME, FORMULA, PicPath)"
                  "VALUES (:NAME, :FORMULA, :PicPath)");

    query.bindValue(0, ui->lineEdit_name->text());
    query.bindValue(1, ui->lineEdit_formula->text());

    QStringList path = picPath.split("/");

    qDebug() << path;

    query.bindValue(2, path[path.size()-1]);

    query.exec();

    query.exec("SELECT * FROM Chemical");
    int col = query.record().count();
    query.last();
    QString msg;
    for( int i = 0 ; i < col; i++){
        msg += query.value(i).toString() + ", ";
    }

    qDebug() << msg;

}

bool AddChemicalDialog::checkDataComplete()
{
    if( ui->lineEdit_name->text() == "") return 0;
    if( ui->lineEdit_formula->text() == "" ) return 0;
    if( ui->lineEdit_picPath->text() == "" ) return 0;

    ui->pushButton->setEnabled(true);
    return 1;
}

void AddChemicalDialog::on_lineEdit_name_editingFinished()
{
    checkDataComplete();
}

void AddChemicalDialog::on_lineEdit_formula_editingFinished()
{
    checkDataComplete();
}
