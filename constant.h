#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>
#include <QStandardPaths>

const QString DESKTOP_PATH = QStandardPaths::locate(QStandardPaths::DesktopLocation, QString(), QStandardPaths::LocateDirectory);
const QString HOME_PATH = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
const QString DATA_PATH = HOME_PATH + "ESR_Data_201610/";
const QString ChemicalPicture_PATH = DATA_PATH + "Chemical_Pic/";
const QString SamplePicture_PATH = DATA_PATH + "ESR_Sample_Pic/";
const QString DB_PATH =  DESKTOP_PATH + "/test.db" ;
#endif // CONSTANT_H
