#include "updatethread.h"

updateThread::uploadThread(){

}
updateThread::~uploadThread(){
    timer->stop();
    delete timer;
    delete Btime;
    sql.clear();
    delete sql;
    delete frep;
}
updateThread::setInfo(QSqlQuery sql, QStandardItemModel *userReadTableModel, QString Btime, int frep){
    this->sql = sql;
    this->userReadTableModel = userReadTableModel;
    this->Btime = Btime;
    this->frep = frep;
}
void updateThread::update(){
    //需要两个额外内容 1 sql句柄 2 table模型
    userReadTableModel ->removeRows(0,userReadTableModel->rowCount());
    sql.exec("SELECT a.`ID`,b.`username`,a.`Station`,a.`Time` FROM infov0 a ,userinfo b where a.`ID` = b.`ID` order by a.`Time`");
    int itemIndex = 0;
    while(sql.next()){
        userReadTableModel->setItem(itemIndex,0,new QStandardItem(sql.value(0).toString()));
        userReadTableModel->setItem(itemIndex,1,new QStandardItem(sql.value(1).toString()));
        userReadTableModel->setItem(itemIndex,2,new QStandardItem(sql.value(2).toString()));
        userReadTableModel->setItem(itemIndex,3,new QStandardItem(sql.value(3).toString()));
        itemIndex++;
    }
}
void updateThread::stop(){
    timer ->stop();
    delete timer;
}
void updateThread::run(){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    int itervalTime = 60/frep*1000;
    timer->start(itervalTime);
}
