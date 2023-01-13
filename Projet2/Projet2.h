#pragma once

#include <QtWidgets/QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "ui_Projet2.h"

class Projet2 : public QMainWindow
{
    Q_OBJECT
	QSerialPort *port;

public:
    Projet2(QWidget *parent = nullptr);
    ~Projet2();

private:
    Ui::Projet2Class ui;

public slots: 
	void onOpenButtonClicked();
	void onSerialPortReadyRead();
	void onSendMessageButtonClicked();
	void generateMessage();

};
