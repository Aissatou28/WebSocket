#include "Projet2.h"

Projet2::Projet2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

	for (int i = 0; i < availablePorts.size(); i++) 
	{
		QSerialPortInfo info = availablePorts[i];
		ui.comboBox->addItem(info.portName(), QVariant(info.portName()));
	}

}

Projet2::~Projet2()
{}



void Projet2::onOpenButtonClicked()
{
	if (ui.comboBox->currentIndex() >= 0) 
	{
		//QSerialPort *port;
		port = new QSerialPort(ui.comboBox->currentText());
		QObject::connect(port, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()));
		port->setBaudRate(9600);
		port->setDataBits(QSerialPort::DataBits::Data8);
		port->setParity(QSerialPort::Parity::NoParity);
		port->setStopBits(QSerialPort::StopBits::OneStop);
		if (port->open(QIODevice::OpenModeFlag::ExistingOnly | QIODevice::OpenModeFlag::ReadWrite));
		{
			ui.statusPort->setText("Statut du port : Ouvert");
		}
	}
}

void Projet2::onSerialPortReadyRead()
{
	
	QByteArray data = port->read(port->bytesAvailable());
	QString str(data);
	ui.textBrowser->insertPlainText(str);
}

void Projet2::generateMessage()
{
	QByteArray data = port->read(port->bytesAvailable());
}

void Projet2::onSendMessageButtonClicked()
{
	if (port->isOpen()) 
	{
		port->write(ui.lineEdit->text().toStdString().c_str());
	}
}


