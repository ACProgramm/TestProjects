
#include <QCoreApplication>
#include "ClientApplication.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    ClientApplication client;
    client.start();

    return app.exec();
}
