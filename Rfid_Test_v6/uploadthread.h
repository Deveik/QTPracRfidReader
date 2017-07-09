#ifndef UPLOADTHREAD_H
#define UPLOADTHREAD_H

#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QSet>
#include <QVariantList>
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <winsock2.h>
#include <RFID_StandardProtocol.h>

class uploadThread : public QObject{
    Q_OBJECT
public :
    explicit uploadThread();
    void setInfo(QSqlQuery sql,hComSocket CS,int frep);
    void stop();
    void run();
    bool getStatus(){return stopped;}
private:
    int frep;
    QSqlQuery sql;
    hComSocket CS;
    QTimer *timer;
    volatile bool stopped;
    QString ByteToHexStr(unsigned char byte_arr[], int arr_len);
private slots:
    void update();
};
#endif // UPLOADTHREAD_H
