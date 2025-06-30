
#include "ClientApplication.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDBusConnection>
#include <QDir>

ClientApplication::ClientApplication(QObject *parent)
    : QObject(parent), timeout_(1000), phrase_("Hello") {
    connect(&timer_, &QTimer::timeout, this, &ClientApplication::updatePhrase);
}

void ClientApplication::start() {
    loadInitialConfig();
    connectToDBus();
    timer_.start(timeout_);
}

void ClientApplication::loadInitialConfig() {
    QString path = QDir::homePath() + "/con.system.configurationManager/confManagerApplication1.json";
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QVariantMap map = doc.object().toVariantMap();
        timeout_ = map["Timeout"].toInt();
        phrase_ = map["TimeoutPhrase"].toString();
    }
}

void ClientApplication::connectToDBus() {
    QString path = "/com/system/configurationManager/Application/confManagerApplication1";
    QString interface = "com.system.configurationManager.Application.Configuration";

    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    sessionBus.connect("com.system.configurationManager",
                       path,
                       interface,
                       "configurationChanged",
                       this,
                       SLOT(onConfigurationChanged(QVariantMap)));
}

void ClientApplication::onConfigurationChanged(QVariantMap newConfig) {
    if (newConfig.contains("Timeout"))
        timeout_ = newConfig["Timeout"].toInt();
    if (newConfig.contains("TimeoutPhrase"))
        phrase_ = newConfig["TimeoutPhrase"].toString();
    timer_.start(timeout_);
}

void ClientApplication::updatePhrase() {
    qDebug() << phrase_;
}
