#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include <QTimer>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>

class updateThread : public QThread{
    Q_OBJECT
public :
    explicit uploadThread(QObject *parent = 0);
    void setInfo(QSqlQuery sql,QStandardItemModel *userReadTableModel,QString Btime,int frep);
    void stop();
    void run();
private:
    QStandardItemModel *userReadTableModel;
    QTimer *timer;
    QString Btime;
    QSqlQuery sql;
    int frep;
private slots:
    void update();
};
#endif // UPDATETHREAD_H
