#include "addsampledialog.h"
#include "ui_addsampledialog.h"

AddSampleDialog::AddSampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSampleDialog)
{
    ui->setupUi(this);

    QDateTime date;

    ui->lineEdit_date->setText(date.currentDateTime().toString("yyyy-MM-dd"));
    ui->label_pic->setText("Drag/Click to\n add Picture.");
    ui->label_spectrum->setText("Drag/Click to\n add Spectrum.");

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
        fileDialog.setDirectory( SAMPLE_PIC_PATH );
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
        fileDialog.setDirectory( SAMPLE_PIC_PATH );
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
    ui->comboBox_chemical->clear();
    ui->comboBox_chemical->addItems(list);
}

void AddSampleDialog::AddSolventList(QStringList list)
{
    ui->comboBox_solvent->clear();
    ui->comboBox_solvent->addItems(list);
}

void AddSampleDialog::CheckDataComplete()
{
    int count = 0;

    if( ui->comboBox_chemical->currentIndex() > 0 ) count ++;
    if( ui->comboBox_solvent->currentIndex() > 0 ) count ++;
    if( ui->lineEdit_sampleName->text() != "" ) count ++;
    if( ui->lineEdit_concentration->text() != "" ) count ++;
    if( ui->lineEdit_maker->text() != "" ) count ++;

    if( ui->lineEdit_picPath->text() != "" ) count ++;
    if( ui->lineEdit_spectrumPath->text() != "" ) count ++;

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

void AddSampleDialog::on_lineEdit_sampleName_editingFinished()
{
    CheckDataComplete();
}

void AddSampleDialog::on_lineEdit_concentration_editingFinished()
{
    CheckDataComplete();
}

void AddSampleDialog::on_lineEdit_maker_editingFinished()
{
    CheckDataComplete();
}

void AddSampleDialog::on_comboBox_chemical_currentIndexChanged(int index)
{
    if( index > 0 ) CheckDataComplete();
}

void AddSampleDialog::on_comboBox_solvent_currentIndexChanged(int index)
{
    if( index > 0 ) CheckDataComplete();
}

void AddSampleDialog::on_pushButton_clicked()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Sample (NAME, Chemical, Solvent, Concentration, Date, Maker, Comment, PicPath, SpectrumPath)"
                  "VALUES (:NAME, :Chemical, :Solvent, :Concentration, :Date, :Maker, :Comment, :PicPath, :SpectrumPath)");

    query.bindValue(":NAME", ui->lineEdit_sampleName->text());
    query.bindValue(":Chemical", ui->comboBox_chemical->currentText());
    query.bindValue(":Solvent", ui->comboBox_solvent->currentText());
    query.bindValue(":Concentration", ui->lineEdit_concentration->text());
    query.bindValue(":Date", ui->lineEdit_date->text());
    query.bindValue(":Maker", ui->lineEdit_maker->text());
    query.bindValue(":Comment", ui->lineEdit_comment->text());

    int len = SAMPLE_PIC_PATH.length();
    QString shortPicPath = picPath.right(picPath.length()-len);
    QString shortSpectPath = spectrumPath.right(spectrumPath.length()-len);

    query.bindValue(":PicPath", shortPicPath);
    query.bindValue(":SpectrumPath", shortSpectPath);

    query.exec();

    ClearEntries();

    query.exec("SELECT * FROM Sample");
    int col = query.record().count();
    query.last();
    QString msg;
    for( int i = 0 ; i < col-1; i++){
        msg += query.value(i).toString() + ", ";
    }
    msg += query.value(col-1).toString();

    //qDebug() << msg;
    ui->lineEdit_picPath->setText("Written to DB.");
    ui->lineEdit_spectrumPath->setText(msg);
}

void AddSampleDialog::ClearEntries()
{
    ui->lineEdit_sampleName->setText("");
    ui->lineEdit_concentration->setText("");
    ui->lineEdit_comment->setText("");
    ui->lineEdit_maker->setText("");
    ui->comboBox_chemical->setCurrentIndex(0);
    ui->comboBox_solvent->setCurrentIndex(0);
    ui->label_pic->setText("Drag/Click to\n add Picture.");
    ui->label_spectrum->setText("Drag/Click to\n add Spectrum.");

    ui->lineEdit_picPath->setText("");
    ui->lineEdit_spectrumPath->setText("");

    ui->pushButton->setEnabled(false);

}
