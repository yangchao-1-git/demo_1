#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include "qcustomplot.h"
#include <QString>
#include <QDateTime>
#include <QTimer>


struct SEND
{
    uchar header;
    uchar mode;
    uchar positionj[4];
    uchar positions[4];
    uchar pitichj[4];
    uchar pitichs[4];
    uchar state;
    uchar check;
    uchar tail;
};

struct RECV
{
    uchar header;
    uchar mode;
    uchar positionz[2];
    uchar positionys[2];
    uchar positionss[2];
    uchar positionssl[2];
    uchar positionssh[2];
    uchar sdsj[2];
    uchar pitichz[2];
    uchar gzqc;
    uchar check;
    uchar tail;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *serialPort;



    QTimer *timSend;
    QTimer *timSend1;//方位角度


private slots:
    void on_openBt_clicked();

    void on_closeBt_clicked();


    void on_fwjdBt_clicked();


    void on_zlfyjdBt_clicked();

public slots:
    void datarecive();

private:
    Ui::MainWindow *ui;
    RECV rece;
    SEND send;
};
#endif // MAINWINDOW_H
