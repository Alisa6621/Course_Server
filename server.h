#pragma once

#include <memory>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "log.h"
#include "response.h"
#include "config.h"

namespace httpserver
{

using TcpServerPtr = std::unique_ptr<QTcpServer>;
using TcpSocketPtr = std::unique_ptr<QTcpSocket>;

class Server : public QObject
{
    Q_OBJECT    //макрос. Необходим, т.к. есть аследование от QObject

public:
    Server();
    virtual ~Server();

    bool run();
    bool setup();

    const Response& getNotFoundPageResponse() const;

    LogPtr getLog() const;

protected:
    void processRequest();

private:
    TcpServerPtr m_tcpServer;
    LogPtr m_log;
    Config m_config;
    Response m_notFoundPageResponse;
    quint16 m_port;             //signed 16-bit integer
};

using ServerPtr = std::unique_ptr<Server>;

}
