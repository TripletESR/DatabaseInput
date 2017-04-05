#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>
#include <QStandardPaths>

const QString DESKTOP_PATH = QStandardPaths::locate(QStandardPaths::DesktopLocation, QString(), QStandardPaths::LocateDirectory);
const QString HOME_PATH = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
const QString DATA_PATH = HOME_PATH + "ESR_Data_201610/";
const QString HALL_DIR_PATH = DATA_PATH + "Hall_data/";
const QString ChemicalPicture_PATH = DATA_PATH + "Chemical_Pic/";
const QString SamplePicture_PATH = DATA_PATH + "ESR_Sample_Pic/";
const QString HALL_PATH = HALL_DIR_PATH + "Hall_pars.txt";
const QString LOG_PATH = DATA_PATH + "DAQ_Log";
const QString DB_PATH = DATA_PATH + "database.db";


#endif // CONSTANT_H