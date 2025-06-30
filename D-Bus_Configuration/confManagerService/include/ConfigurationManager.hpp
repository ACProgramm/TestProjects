
#pragma once

#include <QObject>
#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <QDBusVariant>
#include <QVariantMap>
#include <QMap>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

class ConfigurationManager : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.system.configurationManager.Application.Configuration")

public:
    ConfigurationManager(const QString &appName, QObject *parent = nullptr);
    QVariantMap GetConfiguration() const;
    void ChangeConfiguration(const QString &key, const QDBusVariant &value);

signals:
    void configurationChanged(QVariantMap configuration);

public slots:
    Q_NOREPLY void ChangeConfigurationSlot(const QString &key, const QDBusVariant &value);
    QVariantMap GetConfigurationSlot();

private:
    QString appName_;
    QVariantMap configuration_;
    QString configPath_;
    void loadConfiguration();
    void saveConfiguration();
};
