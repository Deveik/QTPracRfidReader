#include "uploadthread.h"

uploadThread::uploadThread(){
    stopped = true;
}
void uploadThread::setInfo(QSqlQuery sql, hComSocket CS, int frep){
    this->sql = sql;
    this->CS = CS;
    this->frep = frep;
}
void uploadThread::run(){
    if(stopped){
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    }
    int itervalTime = 60/frep*1000;
    timer->start(itervalTime);
    stopped = false;
}
void uploadThread::update(){
    BufferData Data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QSet<QString> tempSet;
    int TagCount = 0;
    int GetCount = 0;
    int status = GEN2_MultiTagInventory(CS,TagCount,0xff);
    if(0x00 == status && TagCount != 0){
        status = BufferM_GetTagData(CS,GetCount,Data,0xff);
        for(int i=0;i<GetCount;i++){
            QString tempStr = ByteToHexStr(Data[i].Data,(Data[i].Len - 1));
            tempSet.insert(tempStr);
        }
    }
    sql.prepare("insert into infov0 values(?,?,?)");

    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QVariantList IDList;
    QVariantList TimeList;
    QVariantList StationList;
    foreach(const QString &value,tempSet){
        IDList<<QVariant(value);
        TimeList<<QVariant(nowTime);
        StationList<<QVariant("1");
    }
    sql.addBindValue(IDList);
    sql.addBindValue(TimeList);
    sql.addBindValue(StationList);
    sql.execBatch();
    sql.clear();
}
void uploadThread::stop(){
    timer ->stop();
    stopped = true;
}
QString uploadThread::ByteToHexStr(unsigned char byte_arr[], int arr_len){
    QString hexstr = QString("");
    for(int i=0; i<arr_len; i++)
    {
        char hex1;
        char hex2;
        int value = byte_arr[i];
        int v1 = value/16;
        int v2 = value % 16;
        //将商转换为字母(change divide to alphabet)
        if (v1>=0 && v1<=9)
        {
            hex1 = (char)(48 + v1);
        }
        else
        {
            hex1 = (char)(55 + v1);
        }
        //将余数转成字母(change remainder to alphabet)
        if (v2>=0 && v2<=9)
        {
            hex2 = (char)(48 + v2);
        }
        else
        {
            hex2 = (char)(55 + v2);
        }
        //将字母连成一串(put alphabet as one string)
        hexstr = hexstr + hex1 + hex2;
    }
    return hexstr;
}
