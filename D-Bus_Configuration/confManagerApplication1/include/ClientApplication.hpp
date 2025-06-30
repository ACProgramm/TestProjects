
#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include <QDBusInterface>

class ClientApplication : public QObject {
    Q_OBJECT

public:
    explicit ClientApplication(QObject *parent = nullptr);
    void start();

private slots:
    void updatePhrase();
    void onConfigurationChanged(QVariantMap newConfig);

private:
    QTimer timer_;
    QString phrase_;
    int timeout_;
    void loadInitialConfig();
    void connectToDBus();
};
