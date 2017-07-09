#include "rfidreader.h"
#include "ui_rfidreader.h"

RFIDReader::RFIDReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RFIDReader){

    ui->setupUi(this);
    //设置tabTable的参数
    ui->tabWidget->setTabText(0,"总体状态表");
    ui->tabWidget->setTabText(1,"数据库");
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabText(2,"用户查看表");
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabText(3,"用户统计图");
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabText(4,"EPCGEN2设置");
    ui->tabWidget->setTabEnabled(5,false);
    ui->tabWidget->setTabText(5,"......");

    //设置表格头
    userReadTableModel = new QStandardItemModel();
    userReadTableModel->setColumnCount(4);
    userReadTableModel->setHeaderData(0,Qt::Horizontal,QString("用户ID"));
    userReadTableModel->setHeaderData(1,Qt::Horizontal,QString("标识符"));
    userReadTableModel->setHeaderData(2,Qt::Horizontal,QString("Staion"));
    userReadTableModel->setHeaderData(3,Qt::Horizontal,QString("时间"));
    ui->tableView->setModel(userReadTableModel);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,200);

    //设置输入栏格式
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);

    //设置按钮默认形态
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_8->setEnabled(false);

    //设置默认的输入内容
    ui->lineEdit->setText("127.0.0.1");
    ui->lineEdit_2->setText("3306");
    ui->lineEdit_5->setText("192.168.1.200");
    ui->lineEdit_6->setText("100");
    ui->lineEdit_7->setText("600");
    ui->lineEdit_8->setText("60");

    //日期控件的设置
    ui->dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_2->setMinimumDate(QDate::currentDate().addDays(-365));
    ui->dateEdit_2->setMaximumDate(QDate::currentDate().addDays(365));
    ui->dateEdit_2->setDisplayFormat("yyyy-MM-dd");

    //Radio控件组设置
    QButtonGroup * qgPicTypeGroup = new QButtonGroup(this);
    qgPicTypeGroup->setExclusive(true);
    qgPicTypeGroup->addButton(ui->radioButton);
    qgPicTypeGroup->addButton(ui->radioButton_2);
    ui->radioButton->setChecked(true);
    QButtonGroup * qgSourceType = new QButtonGroup(this);
    qgSourceType->setExclusive(true);
    qgSourceType->addButton(ui->radioButton_3);
    qgSourceType->addButton(ui->radioButton_4);
    ui->radioButton_3->setChecked(true);
    QButtonGroup * qgReadType = new QButtonGroup(this);
    qgReadType->setExclusive(true);
    qgReadType->addButton(ui->radioButton_5);
    qgReadType->addButton(ui->radioButton_6);
    ui->radioButton_5->setChecked(true);

    //下拉框选项绑定
    ui->comboBox->addItem("10");
    ui->comboBox->addItem("50");
    ui->comboBox->addItem("200");
    ui->comboBox->addItem("1000");

    //QPushButton绑定事件
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(connectMysql()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(generatePic()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(connectDevice()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(addCondition()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(realTimeMonitor()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(readPastInfo()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(stopRealTimeM()));
        
    //QThread线程设置
    upThread = new uploadThread();

    //QTimer设置
    updateTableTimer = new QTimer(this);
    connect(this->updateTableTimer,SIGNAL(timeout()),this,SLOT(updateTable()));

    //QListView设置
    QStringListModel * ConditionListModel = new QStringListModel();
    ui->listView ->setModel(ConditionListModel);
    ConditionListModel->setStringList(conditionList);

    //QCustomPlot设置
    ui->widget_2->hide();
}

void RFIDReader::connectMysql(){
    bool connectFlag = true;
    {
        QSqlDatabase tempSqldb = QSqlDatabase::addDatabase("QMYSQL","rfidDB");
        tempSqldb.setDatabaseName("rfidreaderv0");
        tempSqldb.setHostName(ui->lineEdit->text());
        tempSqldb.setPort(ui->lineEdit_2->text().toInt());
        connectFlag = tempSqldb.open(ui->lineEdit_3->text(),ui->lineEdit_4->text());
        mySqlerr = tempSqldb.lastError();
        tempSqldb.close();
    }
    if(!connectFlag){
        QSqlDatabase::removeDatabase(("rfidDB"));
    }else{
        mySqldb = QSqlDatabase::addDatabase("QMYSQL","rfidDB");
        mySqldb.setDatabaseName("rfidreaderv0");
        mySqldb.setHostName(ui->lineEdit->text());
        mySqldb.setPort(ui->lineEdit_2->text().toInt());
        mySqldb.open(ui->lineEdit_3->text(),ui->lineEdit_4->text());
    }
    setMysqlError();
}
void RFIDReader::addCondition(){
    if(conditionList.length()<1){
        conditionList += ui->dateEdit->text() ;
        conditionList += ui->dateEdit_2->text() ;
    }
    conditionList += ui->timeEdit->text();
    conditionList += ui->timeEdit_2->text();
    QStringListModel * ConditionListModel = new QStringListModel();
    ui->listView ->setModel(ConditionListModel);
    ConditionListModel->setStringList(conditionList);
}
void RFIDReader::connectDevice(){
    QString ipAddr = ui->lineEdit_5->text();
    int port = ui->lineEdit_6->text().toInt();
    int rVal = Socket_ConnectSocket(&sockClient,ipAddr.toLatin1().data(),port);
    if(rVal == 0){
        ui->pushButton_4->setEnabled(false);
        uploadFrepInMinute = ui->lineEdit_7->text().toInt();
        uploadFrepInMinute = ui->lineEdit_8->text().toInt();
        ui->label_31->setText("连接成功");
        ui->label_39->setText("连接成功");
        CS.hCom = NULL;
        CS.sockClient = sockClient;
        int PLen = 6;
        unsigned char ReaderAddr;
        unsigned char major = 0;
        unsigned char minor = 0;
        unsigned char PAddr = 0x10;
        unsigned char PRefData[1024] = {0};
        ReaderAddr = (unsigned char)(255&0xff);
        QString tempVersion;
        QString tempSerial;
        if(0x00 == Config_GetLocatorVersion(CS,major,minor,ReaderAddr))
            tempVersion = QString("Version: 0%1.0%2").arg(major).arg(minor);
        if(0x00 == Parameter_GetReader(CS,PAddr,PLen,PRefData,ReaderAddr))
            tempSerial += "Serial: " + ByteToHexStr(PRefData,PLen);
        ui->label_36->setText(tempVersion);
        ui->label_37->setText(tempSerial);
        ui->label_32->setText("正常连接");
        ui->label_34->setText("是");
        ui->pushButton_6->setEnabled(true);
    }else{
        switch (rVal) {
        case (101):
            ui->label_31->setText("数据发送错误");
            break;
        case (201):
            ui->label_31->setText("数据接受错误");
            break;
        case (301):
            ui->label_31->setText("数据解析错误");
            break;
        case (401):
            ui->label_31->setText("数据校验错误");
            break;
        default:
            ui->label_31->setText(QString("未知错误编码:%1").arg(rVal));
            break;
        }
    }
}
void RFIDReader::setMysqlError(){
    switch (mySqlerr.type()) {
    case (0):
        ui->label_5->setText("Tips: 成功连接");
        ui->label_9->setText("成功连接");
        ui->pushButton->setEnabled(false);
        ui->tabWidget->setTabEnabled(2,true);
        ui->tabWidget->setTabEnabled(3,true);
        ui->tabWidget->setTabEnabled(4,true);
        ui->label_38->setText("连接成功");
        queryBasicInfo();
        break;
    case (1):
        ui->label_5->setText(QString("Tips:  %1 %2").arg(mySqlerr.databaseText()).arg(mySqlerr.driverText()));
        ui->label_9->setText("连接异常");
        break;
    case (2):
        ui->label_5->setText(QString("Tips:  %1 %2").arg(mySqlerr.databaseText()).arg(mySqlerr.driverText()));
        ui->label_9->setText("语句错误");
    default:
        ui->label_5->setText(QString("Tips:  %1 %2").arg(mySqlerr.databaseText()).arg(mySqlerr.driverText()));
        ui->label_9->setText("未知错误");
        break;
    }
}
void RFIDReader::readPastInfo(){
    QSqlQuery sql("",mySqldb);
    userReadTableModel ->removeRows(0,userReadTableModel->rowCount());
    QString Statement = "SELECT a.`ID`,b.`username`,a.`Station`,a.`Time` FROM infov0 a ,userinfo b where a.`ID` = b.`ID`";
    QString dataNum = ui->comboBox->currentText();
    if(!ui->radioButton_5->isChecked())
        Statement += " order by a.`Time` DESC";
    Statement += QString(" limit 0,%1").arg(dataNum);
    sql.exec(Statement);
    userReadTableModel ->removeRows(0,userReadTableModel->rowCount());
    int itemIndex = 0;
    while(sql.next()){
        userReadTableModel->setItem(itemIndex,0,new QStandardItem(sql.value(0).toString()));
        userReadTableModel->setItem(itemIndex,1,new QStandardItem(sql.value(1).toString()));
        userReadTableModel->setItem(itemIndex,2,new QStandardItem(sql.value(2).toString()));
        userReadTableModel->setItem(itemIndex,3,new QStandardItem(sql.value(3).toString()));
        itemIndex++;
    }
}
void RFIDReader::queryBasicInfo(){
    QSqlQuery sql("",mySqldb);
    sql.exec("show tables");
    QString MyTablesList ;
    while(sql.next()){
       MyTablesList += sql.value(0).toString() + " ";
    }
    sql.exec("select count(*) from infov0");
    sql.next();
    QString infoNum = sql.value(0).toString();
    sql.exec("select count(*) from userinfo");
    sql.next();
    QString uInfoNum = sql.value(0).toString();
    ui->label_10->setText(MyTablesList);
    ui->label_11->setText(infoNum);
    ui->label_13->setText(uInfoNum);
    sql.clear();
}
void RFIDReader::generatePic(){
    if(ui->radioButton->isChecked())
        generateLineChart();
    else
        generateColumn();
}
void RFIDReader::realTimeMonitor(){
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
    ui->label_40->setText("正在工作");
    //开启双线程 一个用于上传数据
    QSqlQuery sql1("",mySqldb);
    if(this->upThread->getStatus()){
        this->upThread->setInfo(sql1,CS,60);
        this->upThread->run();
    }
    //一个用于更新数据
    this->updateTableTimer->start(1000);
    BeginTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->label_35->setText(BeginTime);
}
void RFIDReader::updateTable(){
    userReadTableModel ->removeRows(0,userReadTableModel->rowCount());
    QString statement = QString("SELECT a.`ID`,b.`username`,a.`Station`,a.`Time` FROM infov0 a ,userinfo b where a.`Time`>'%1' and a.`ID` = b.`ID` order by a.`Time`").arg(BeginTime);
    QSqlQuery sql("",mySqldb);
    sql.exec(statement);
    int itemIndex = 0;
    while(sql.next()){
        userReadTableModel->setItem(itemIndex,0,new QStandardItem(sql.value(0).toString()));
        userReadTableModel->setItem(itemIndex,1,new QStandardItem(sql.value(1).toString()));
        userReadTableModel->setItem(itemIndex,2,new QStandardItem(sql.value(2).toString()));
        userReadTableModel->setItem(itemIndex,3,new QStandardItem(sql.value(3).toString()));
        itemIndex++;
    }
}
void RFIDReader::stopRealTimeM(){
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    this->updateTableTimer->stop();
    this->upThread->stop();
    ui->label_40->setText("停止工作");
}
void RFIDReader::generateLineChart(){
    ui->widget_2->hide();
    ui->widget->show();
    QCustomPlot *customPlot = ui->widget;
    customPlot->clearGraphs();
    customPlot->addGraph();
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(255, 200, 20, 200));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2.0);

    customPlot->graph()->setPen(pen);
    // customPlot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
    // set graph name, will show up in legend next to icon:
    customPlot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
    // set data:
    QVector<double> yVal, value;
    QDate begin = QDate::fromString(ui->dateEdit->text(),"yyyy-MM-dd");
    QDate end = QDate::fromString(ui->dateEdit_2->text(),"yyyy-MM-dd");
    QSqlQuery sql("",mySqldb);
    if(ui->radioButton_3->isChecked()){
        sql.prepare("SELECT count(*) FROM infov0 where year(`Time`) = ? and month(`Time`) = ?");
        //编排月份 将月份的记录次数记录下来
        QVariantList YearList;
        QVariantList MonthList;
        int begin_year = begin.year();
        int begin_month = begin.month();
        int end_year = end.year();
        int end_month = end.month();
        if(begin_year==end_year)
            for(int i=begin_month;i<end_month;i++){
                sql.bindValue(0,begin_year);
                sql.bindValue(1,i);
                sql.exec();
                sql.next();
                yVal << sql.value(0).toString().toDouble();
                value<< double(i);
            }
        else{
            while(begin_year<end_year){
                while(begin_month<=12){
                    sql.bindValue(0,begin_year);
                    sql.bindValue(1,begin_month);
                    sql.exec();
                    sql.next();
                    yVal << sql.value(0).toString().toDouble();
                    value<< double(begin_month);
                    begin_month++;
                }
                begin_year++;
            }
            for(int i=1;i<end_month;i++){
                sql.bindValue(0,begin_year);
                sql.bindValue(1,i);
                sql.exec();
                sql.next();
                yVal << sql.value(0).toString().toDouble();
                value<< double(i);
            }
        }
        sql.addBindValue(YearList);
        sql.addBindValue(MonthList);
        sql.execBatch();
        while(sql.next()){
            yVal<< sql.value(0).toString().toDouble();
        }
    }else{
        sql.prepare("SELECT count(*) FROM infov0 where month(`Time`) = ? and day(`Time`) = ?");
        //编排日期 将日期的记录下来
        for(;begin<end;begin= begin.addDays(1)){
            sql.bindValue(0,begin.month());
            sql.bindValue(1,begin.day());
            sql.exec();
            sql.next();
            yVal << sql.value(0).toString().toDouble();
            value << double(begin.day());
        }
    }
    customPlot->graph()->setData(value , yVal);
    customPlot->xAxis2->setVisible(false);
    customPlot->yAxis2->setVisible(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setSubTicks(false);
    customPlot->yAxis2->setSubTicks(false);

    customPlot->xAxis->setRange(value.value(0), (value.value(0)+value.length()-1+0.2));
    double max_yVal = 3;
    for(int i=0;i<yVal.length();i++){
        if(yVal.value(i)>max_yVal) max_yVal = yVal.value(i);
    }
    customPlot->yAxis->setRange(0, max_yVal+0.2);

    // setup legend:
    customPlot->legend->setFont(QFont(font().family(), 7));
    customPlot->replot();
}
void RFIDReader::generateColumn(){
    ui->widget->hide();
    ui->widget_2->show();
    QCustomPlot *customPlot = ui->widget_2;
    customPlot->clearGraphs();
    customPlot->addGraph();

    QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    // set names and colors:
    regen->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    regen->setBrush(QColor(111, 9, 176));

    // Add data:
    QVector<double> regenData;
    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    //解析QStringList
    QString begin = conditionList.value(0);
    QString end = conditionList.value(1);

    QStringList tempXIndex;
    QSqlQuery sql("",mySqldb);
    //添加下坐标
    QString preStatement = QString("SELECT count(*) FROM rfidreaderv0.infov0 where Time >= '%1' and Time< '%2' and ").arg(begin).arg(end);
    for(int i=2;i<conditionList.length();i+=2){
        QString execSql = preStatement
                + QString("Time > date_add(DATE_FORMAT(Time,'%Y-%m-%d'),INTERVAL '%1' HOUR_MINUTE) and ").arg(conditionList.value(i))
                + QString("Time < date_add(DATE_FORMAT(Time,'%Y-%m-%d'),INTERVAL '%2' HOUR_MINUTE)").arg(conditionList.value(i+1));
        labels << QString("%1-%2").arg(conditionList.value(i)).arg(conditionList.value(i+1));
        qDebug() << execSql;
        sql.exec(execSql);
        sql.next();
        regenData << sql.value(0).toString().toDouble();
    }

    int yLength = (conditionList.length()-2)/2;
    for(int i=1;i<=yLength;i++){
        ticks << i;
    }
    int max = 3;
    for(int i=0;i<regenData.length();i++){
        if(max<regenData.value(i))
            max = regenData.value(i);
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);

    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);

    customPlot->xAxis->setRange(0, yLength + 1.2);
    customPlot->yAxis->setRange(0, max + 0.2);
    regen->setData(ticks, regenData);

    customPlot->replot();
}
QString RFIDReader::ByteToHexStr(unsigned char byte_arr[], int arr_len){
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
RFIDReader::~RFIDReader(){
    Socket_CloseSocket(sockClient);
    delete ui;
}

void RFIDReader::on_radioButton_2_clicked(){
    ui->pushButton_5->setEnabled(true);
}

void RFIDReader::on_radioButton_clicked()
{
    ui->pushButton_5->setEnabled(false);
    conditionList.clear();
    QStringListModel * ConditionListModel = new QStringListModel();
    ui->listView ->setModel(ConditionListModel);
    ConditionListModel->setStringList(conditionList);
}
