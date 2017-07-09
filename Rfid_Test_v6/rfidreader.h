#ifndef RFIDREADER_H
#define RFIDREADER_H

#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QButtonGroup>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QTimer>

#include <QDebug>

#include <winsock2.h>
#include <RFID_StandardProtocol.h>

#include "uploadthread.h"

namespace Ui {
class RFIDReader;
}

class RFIDReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit RFIDReader(QWidget *parent = 0);
    ~RFIDReader();

private:
    Ui::RFIDReader *ui;
    QSqlError mySqlerr;
    QSqlDatabase mySqldb;

    hComSocket CS;
    SOCKET sockClient = 0;

    int uploadFrepInMinute;
    int updateFrepInMinute;

    QStandardItemModel *userReadTableModel;

    bool updateTimerFlag;
    QString BeginTime;
    QTimer *updateTableTimer;

    void setMysqlError();
    void queryBasicInfo();

    uploadThread *upThread;

    QStringList conditionList;

    QString ByteToHexStr(unsigned char byte_arr[], int arr_len);
    void generateLineChart();
    void generateColumn();

private slots:
    void connectMysql();
    void connectDevice();
    void realTimeMonitor();
    void readPastInfo();
    void generatePic();
    void updateTable();
    void stopRealTimeM();
    void addCondition();
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
};

#endif // RFIDREADER_H
