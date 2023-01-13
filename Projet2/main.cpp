#include "Projet2.h"
#include <QtWidgets/QApplication>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>


QString generateMessage(const QString& message) {
	// Générer un message à partir du message reçu
	return QString("Message généré : %1").arg(message);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// Créez un serveur WebSocket sur le port 12345
	QWebSocketServer server(QStringLiteral("Echo Server"),
		QWebSocketServer::NonSecureMode);
	if (!server.listen(QHostAddress::AnyIPv4, 12345)) {
		qFatal("Erreur lors de l'écoute du serveur.");
		return 1;
	}
	QObject::connect(&server, &QWebSocketServer::newConnection,
		[&server]() {
		QWebSocket* pSocket = server.nextPendingConnection();
		QObject::connect(pSocket, &QWebSocket::textMessageReceived,
			[pSocket](const QString& message) {
			// Recevoir le message
			qDebug() << "Reçu : " << message;


			// Envoyer un message de retour
			bool boucle = true;
			while (boucle) {
				// Appeler la fonction pour générer le message
				QString messageToSend = generateMessage(message);
				pSocket->sendTextMessage(messageToSend);
		
				boucle = false;
		
	});

    Projet2 w;
    w.show();
    return a.exec();
}
