#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <stdio.h>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*status = Version(&reader);
    if (status == MI_OK){
        qDebug() << "Reader firwmare is \n" << reader.version;
    }

    status = LEDBuzzer(&reader, LED_GREEN_ON);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connect_clicked()
{
    reader.Type = ReaderCDC;
    reader.device = 0;

    int16_t status = OpenCOM(&reader);
    if (status != MI_OK){
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Lecteur non trouvé !");
        messageBox.setFixedSize(500,200);
    }
    else{
        if(reader.Type==ReaderCDC){
            this->ui->connect->setText("Connecté (PORT " + QString::number((int)reader.device) + ")");
            this->ui->connect->setEnabled(false);
            this->ui->disconnect->setEnabled(true);
        }
    }
}

void MainWindow::on_disconnect_clicked()
{

}
