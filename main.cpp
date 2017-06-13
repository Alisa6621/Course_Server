#include <QCoreApplication>  //обработка сообщений консольного приложения

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    auto server = httpserver::ServerPtr(new httpserver::Server());  //auto  - компилятор сам определяет тип переменной
    if (!server->setup() || !server->run())
    {
        return 1;
    }

    return app.exec();
}
