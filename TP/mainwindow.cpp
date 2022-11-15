#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <stdio.h>

#include "LIB/MfErrNo.h"
#include "LIB/Core.h"
#include "LIB/Sw_Device.h"
#include "LIB/Sw_Mf_Classic.h"
#include "LIB/Sw_Poll.h"
#include "LIB/Sw_ISO14443A-3.h"
#include "LIB/TypeDefs.h"
#include "LIB/Tools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int16_t status = MI_OK;
    char s_buffer[64];


    ReaderName reader;
    reader.Type = ReaderCDC;
    reader.device = 0;

    status = OpenCOM(&reader);
    if (status != MI_OK){
        printf("Reader not found\n");
    }
    else{
        switch(reader.Type)
        {
            case ReaderTCP:
                sprintf(s_buffer, "IP : %s", reader.IPReader);
            break;
            case ReaderCDC:
                sprintf(s_buffer, "COM%d", reader.device);
            break;

        }
        printf("Reader found on %s\n", s_buffer);
    }


    status = Version(&reader);
    if (status == MI_OK){
        printf("Reader firwmare is %s\n", reader.version);
        printf("Reader serial is %02X%02X%02X%02X\n", reader.serial[0], reader.serial[1], reader.serial[2], reader.serial[3]);
        printf("Reader stack is %s\n", reader.stack);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

