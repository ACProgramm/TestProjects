
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include "ConfigurationManager.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString appName = "confManagerApplication1";
    QString objectPath = "/com/system/configurationManager/Application/" + appName;

    ConfigurationManager *manager = new ConfigurationManager(appName);
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    sessionBus.registerService("com.system.configurationManager");
    sessionBus.registerObject(objectPath, manager,
                              QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);

    return app.exec();
}
