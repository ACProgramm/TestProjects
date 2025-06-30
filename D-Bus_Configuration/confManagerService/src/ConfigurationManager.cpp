
#include "ConfigurationManager.hpp"
#include <QDebug>
#include <QDir>

ConfigurationManager::ConfigurationManager(const QString &appName, QObject *parent)
    : QObject(parent), appName_(appName) {
    configPath_ = QDir::homePath() + "/com.system.configurationManager/" + appName_ + ".json";
    loadConfiguration();
}

void ConfigurationManager::loadConfiguration() {
    QFile file(configPath_);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        configuration_ = doc.object().toVariantMap();
    }
}

void ConfigurationManager::saveConfiguration() {
    QFile file(configPath_);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj = QJsonObject::fromVariantMap(configuration_);
        file.write(QJsonDocument(obj).toJson());
    }
}

void ConfigurationManager::ChangeConfiguration(const QString &key, const QDBusVariant &value) {
    configuration_[key] = value.variant();
    saveConfiguration();
    emit configurationChanged(configuration_);
}

QVariantMap ConfigurationManager::GetConfiguration() const {
    return configuration_;
}

void ConfigurationManager::ChangeConfigurationSlot(const QString &key, const QDBusVariant &value) {
    ChangeConfiguration(key, value);
}

QVariantMap ConfigurationManager::GetConfigurationSlot() {
    return GetConfiguration();
}
