#include "addsampledialog.h"
#include "ui_addsampledialog.h"

AddSampleDialog::AddSampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSampleDialog)
{
    ui->setupUi(this);

    QDateTime date;

    ui->lineEdit_date->setText(date.currentDateTime().toString("yyyy-MM-dd"));

}

AddSampleDialog::~AddSampleDialog()
{
    delete ui;
}

void AddSampleDialog::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void AddSampleDialog::dragMoveEvent(QDragMoveEvent *event)
{
    QFont font = ui->label_pic->font();
    if(ui->label_pic->geometry().contains(event->pos())){
        font.setBold(true);
        ui->label_pic->setFont(font);
    }else{
        font.setBold(false);
        ui->label_pic->setFont(font);
    }

    font = ui->label_spectrum->font();
    if(ui->label_spectrum->geometry().contains(event->pos())){
        font.setBold(true);
        ui->label_spectrum->setFont(font);
    }else{
        font.setBold(false);
        ui->label_spectrum->setFont(font);
    }
}

void AddSampleDialog::dropEvent(QDropEvent *event)
{
    const QMimeData * mimeData = event->mimeData();

    if( ui->label_pic->geometry().contains(event->pos()) ) {

        SetPicture(ui->label_pic,
                   ui->lineEdit_picPath,
                   picPath,
                   mimeData->urls().at(0).toLocalFile());

    }

    if( ui->label_spectrum->geometry().contains(event->pos()) ) {

        SetPicture(ui->label_spectrum,
                   ui->lineEdit_spectrumPath,
                   spectrumPath,
                   mimeData->urls().at(0).toLocalFile());

    }

    CheckDataComplete();

}

void AddSampleDialog::mousePressEvent(QMouseEvent *mouse)
{
    bool inPic = ui->label_pic->geometry().contains(mouse->pos());
    bool inSpect = ui->label_spectrum->geometry().contains(mouse->pos());

    if( inPic ){
        QFileDialog fileDialog(this);
        //fileDialog.setNameFilter("Picture (*bmp *png *jpg *jpeg *gif)");
        fileDialog.setReadOnly(1);
        fileDialog.setDirectory( SamplePicture_PATH );
        QString fileName;
        if( fileDialog.exec() ){
            QStringList fileNames = fileDialog.selectedFiles();
            fileName = fileNames[0];
        }
        //qDebug() << fileName;

        if( fileName == ""){
            ui->lineEdit_picPath->setText("no file seleced.");
            ui->pushButton->setEnabled(false);
        }else{
            SetPicture(ui->label_pic, ui->lineEdit_picPath, picPath, fileName);
            CheckDataComplete();
        }

        return;
    }

    if( inSpect ){
        QFileDialog fileDialog(this);
        //fileDialog.setNameFilter("Picture (*bmp *png *jpg *jpeg *gif)");
        fileDialog.setReadOnly(1);
        fileDialog.setDirectory( SamplePicture_PATH );
        QString fileName;
        if( fileDialog.exec() ){
            QStringList fileNames = fileDialog.selectedFiles();
            fileName = fileNames[0];
        }
        //qDebug() << fileName;

        if( fileName == ""){
            ui->lineEdit_spectrumPath->setText("no file seleced.");
            ui->pushButton->setEnabled(false);
        }else{
            SetPicture(ui->label_spectrum, ui->lineEdit_spectrumPath, spectrumPath, fileName);
            CheckDataComplete();
        }

        return;
    }



}

void AddSampleDialog::AddChemicalList(QStringList list)
{
    ui->comboBox_chemical->addItems(list);
}

void AddSampleDialog::AddSolventList(QStringList list)
{
    ui->comboBox_solvent->addItems(list);
}

void AddSampleDialog::CheckDataComplete()
{
    int count = 0;

    if( ui->comboBox_chemical->currentIndex() > 0 ) count ++;
    if( ui->comboBox_solvent->currentIndex() > 0 ) count ++;
    if( !ui->lineEdit_sampleName->text().isNull() ) count ++;
    if( !ui->lineEdit_concentration->text().isNull() ) count ++;
    if( !ui->lineEdit_maker->text().isNull() ) count ++;

    if( !ui->lineEdit_picPath->text().isNull() ) count ++;
    if( !ui->lineEdit_spectrumPath->text().isNull() ) count ++;

    //if( !ui->lineEdit_comment->text().isNull() ) count ++;

    ui->pushButton->setEnabled( count == 7 );
}

void AddSampleDialog::SetPicture(QLabel *label, QLineEdit * lineEdit, QString &sysPath, QString path)
{
    sysPath = path;

    QImage image(sysPath);
    int imageH = image.height();
    int imageW = image.width();

    int labelH = label->geometry().height();
    int labelW = label->geometry().width();

    QImage scaledImage;
    if( 1.*imageH/imageW > 1.*labelH/labelW){
        scaledImage = image.scaledToHeight(labelH);
    }else{
        scaledImage = image.scaledToWidth(labelW);
    }

    label->setPixmap( QPixmap::fromImage( scaledImage) );
    lineEdit->setText(sysPath);

}
