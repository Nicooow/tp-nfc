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
            LEDBuzzer(&reader, LED_RED_ON);
        }
    }
}

void MainWindow::on_disconnect_clicked()
{
    LEDBuzzer(&reader, LED_OFF);
    RF_Power_Control(&reader, FALSE, 0);
    CloseCOM(&reader);
    this->ui->connect->setText("Connexion");
    this->ui->connect->setEnabled(true);
    this->ui->disconnect->setEnabled(false);
}

int MainWindow::readCard(int bloc, char *data, int keyIndex) {
    int status = Mf_Classic_Read_Block(&reader, TRUE, bloc, (uint8_t*) data, AuthKeyA, keyIndex);
    return status;
}

void MainWindow::on_read_clicked()
{
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;
    char data[240];


   RF_Power_Control(&reader, TRUE, 0);
   int status = ISO14443_3_A_PollCard(&reader, atq, sak, uid, &uid_len);
   if (status != MI_OK){
       qDebug()<<"Load Key [FAILED]\n";
   }
   else{
       LEDBuzzer(&reader, BUZZER_ON);
       readCard(9, data, 2);
       ui->inputPrenom->setText(data);
       readCard(10, data, 2);
       ui->inputNom->setText(data);
       DELAYS_MS(20);
   }
   LEDBuzzer(&reader, BUZZER_OFF);
}


void MainWindow::on_update_clicked()
{
    int status = 0;
    unsigned char nom[16];
    unsigned char prenom[16];
    char data[240];

    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;

    RF_Power_Control(&reader, TRUE, 0);
    status = ISO14443_3_A_PollCard(&reader, atq, sak, uid, &uid_len);

    strncpy((char*)nom, ui->inputNom->text().toUtf8().data(), 16);
    status = Mf_Classic_Write_Block(&reader, TRUE, 10, (uint8_t*) nom, AuthKeyB, 2);

    strncpy((char*)prenom, ui->inputPrenom->text().toUtf8().data(), 16);
    status = Mf_Classic_Write_Block(&reader, TRUE, 9, (uint8_t*) prenom, AuthKeyB, 2);

    readCard(9, data, 2);
    ui->inputPrenom->setText(data);
    readCard(10 ,data, 2);
    ui->inputNom->setText(data);
}

