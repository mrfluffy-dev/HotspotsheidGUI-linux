#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<thread>
#include <QTimer>
using namespace std;
bool connected = false;
string labletext ;

string GetStdoutFromCommand(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
          pclose(stream);
      }
    return data;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->BtnConDis, SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::TimerSlot );
    ConnectStatus();
}
void MainWindow::ConnectStatus(){
    ui->label->setText(GetStdoutFromCommand("hotspotshield status").c_str());
    if(ui->label->text().contains("disconnected")){
        ui->BtnConDis->setText("Connect");
        connected = false;
    }
    else {
        ui->BtnConDis->setText("Disconnect");
        connected = true;
    }
    timer->start(1000);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onButtonClicked()
{
    if(connected == false){
        string location = "hotspotshield connect " + ui->Location->currentText().toStdString();
        const char *lc = location.c_str();
        system(lc);
    }
    else {
        string location = "hotspotshield disconnect";
        const char *lc = location.c_str();
        system(lc);
    }
    ConnectStatus();
}
void MainWindow::TimerSlot()
{
    ConnectStatus();
}

