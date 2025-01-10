#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList serialNamePort;
    serialPort = new QSerialPort(this);

    connect(serialPort,SIGNAL(readyRead()),this,SLOT(datarecive()));


    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        serialNamePort<<info.portName();
    }
    ui->serialCb->addItems(serialNamePort);




    timSend=new QTimer;
    timSend->setInterval(1000);
    connect(timSend,&QTimer::timeout,this,[=]()
    {
        on_fwjdBt_clicked();
    });

    timSend1=new QTimer;
    timSend1->setInterval(1000);
    connect(timSend1,&QTimer::timeout,this,[=]()
    {
        on_zlfyjdBt_clicked();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_openBt_clicked()
{
    serialPort->setPortName(ui->serialCb->currentText());
    serialPort->setBaudRate(QSerialPort::Baud115200);

    if(serialPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::critical(this,"提示","失败");
    }
}



void MainWindow::datarecive(){
    QByteArray buffer;
    {
        buffer = serialPort->readAll();
    }
//     ui->recvEdit->appendPlainText(buffer);
//    int a = buffer[0];
//    while(!buffer.isEmpty() && !(a == -86))
//        buffer.remove(0,1);

//    int check = 0;
//    for(int i = 1;i<21;i++)
//    {
//        check += buffer[i];
//    }
//    if(!buffer.isEmpty()){
//        RECV *get;
//        get = (RECV*)buffer.data();

//        rece.mode = get->mode;
//        if(get->header==0xAA && get->tail==0x55 && get->check == check){

//        }
//    }
}
void MainWindow::on_fwjdBt_clicked(){

     memset(&send,0,21);
     send.header = 0xAA;
     send.tail = 0x55;
     send.mode = 0x01;
     send.check = 0;
     double temp = ui->fwjdEdit->text().toDouble();
     temp += 180;
     int temp1 = temp*10000;

     send.positionj[0] = (uchar)(temp1 >> 24);
     send.positionj[1] = (uchar)(temp1 >> 16);
     send.positionj[2] = (uchar)(temp1 >> 8);
     send.positionj[3] = (uchar)(temp1 & 0xff);

     send.check =send.mode + send.positionj[0] +send.positionj[1] +send.positionj[2] +send.positionj[3];

    QByteArray byteArray;
    byteArray.append(reinterpret_cast<char *>(&send), 21);

    serialPort->write(byteArray);

//    timSend->start(20);

}


void MainWindow::on_closeBt_clicked()
{
    serialPort->close();
}



void MainWindow::on_zlfyjdBt_clicked()
{
    memset(&send,0,21);
    send.header = 0xAA;
    send.tail = 0x55;
    send.mode = 0x01;
    send.check = 0;
    double temp = ui->zlfyjdEdit->text().toDouble();
    int temp1 = temp*10000;

    send.pitichj[0] = (uchar)(temp1 >> 24);
    send.pitichj[1] = (uchar)(temp1 >> 16);
    send.pitichj[2] = (uchar)(temp1 >> 8);
    send.pitichj[3] = (uchar)(temp1 & 0xff);
    send.check =send.mode + send.pitichj[0] +send.pitichj[1] +send.pitichj[2] +send.pitichj[3];

    QByteArray byteArray;
    byteArray.append(reinterpret_cast<char *>(&send), 21);

    serialPort->write(byteArray);

//    timSend1->start(20);
}
