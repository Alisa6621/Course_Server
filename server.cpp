#include "server.h"
#include "request.h"
#include "response.h"

#include <iostream>
#include <QFile>
#include <QDataStream>

namespace httpserver
{

    std::map<QString, QString> mimeTypes =
    {
        std::make_pair("ico", "image/x-icon"),
        std::make_pair("png", "image/png"),
        std::make_pair("jpg", "image/jpeg"),
        std::make_pair("jpeg", "image/jpeg"),
        std::make_pair("html", "text/html;charset=UTF-8"),
        std::make_pair("css", "text/css;charset=UTF-8"),
        std::make_pair("js", "application/javascript;charset=UTF-8"),
        std::make_pair("bmp", "image/bmp"),
    };

    //////////////////////////////////////////////////////////////////////////////

    Server::Server()
        : QObject()
    {
        m_log.reset(new Log());

        m_port = 8089; //выбор порта 8089
        m_tcpServer.reset(new QTcpServer());
    }

    //////////////////////////////////////////////////////////////////////////////

    Server::~Server()
    {
        if (!!m_tcpServer)
        {
            m_tcpServer->close();
        }

        m_log->printLn(LogTag::Info, QString("Server stopped."));
    }

    //////////////////////////////////////////////////////////////////////////////

    bool Server::run()
    {
        if (!m_tcpServer->listen(QHostAddress::Any, m_port))
        {
            std::cerr << "Failed to establish server!" << std::endl;
            return false;
        }

        // Add new connection callback
        connect(m_tcpServer.get(), &QTcpServer::newConnection, this, &Server::processRequest);

        std::cout << "Server established successfully! Port [" << m_port << "]" << std::endl;
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////

    void Server::processRequest()
    {
        auto clientConnection = TcpSocketPtr(m_tcpServer->nextPendingConnection());

        clientConnection->waitForReadyRead();
        QByteArray requestData = clientConnection->readAll();

        //запрос
        Request request = Request(requestData);
        m_log->printLn(LogTag::Info, QString("Request. Method: %1; URL: %2").arg(request.getMethodStr(request.getMethod()), request.getUri()));

        //отправление ответа
        Response response;
        QString serverUri = m_config.getRootLocation() + request.getUri();

        QFile f(serverUri);
        QByteArray content;
        if (!f.open(QFile::ReadOnly))
        {
            response = getNotFoundPageResponse();
        }
        else
        {
            QDataStream in(&f);
            uint fileSize = f.size();
            content.resize(fileSize);

            in.readRawData(content.data(), fileSize);

            response.setContent(content);

            int extensionPos = serverUri.lastIndexOf('.');
            if (extensionPos != -1)
            {
                QString extension = serverUri.right(serverUri.length() - extensionPos - 1);

                auto mimeTypeIt = mimeTypes.find(extension);
                if (mimeTypeIt != mimeTypes.end())
                {
                    response.setHeader("Content-Type", mimeTypeIt->second);
                }
            }

            response.setStatus(HttpStatus::Code::Success);
        }

        QByteArray responseBody = response.construct();
        clientConnection->write(responseBody);
        clientConnection->flush();

        //закрываем соединение
        clientConnection->disconnectFromHost();
    }

    //////////////////////////////////////////////////////////////////////////////

    LogPtr Server::getLog() const
    {
        return m_log;
    }

    //////////////////////////////////////////////////////////////////////////////

    bool Server::setup()
    { 
        if (!m_config.load())
            return false;

        m_port = m_config.getPort();
        m_notFoundPageResponse.setStatus(HttpStatus::NotFound);

        QFile notFoundPageFile(m_config.getNotFoundPageLocation());
        if (!notFoundPageFile.open(QFile::ReadOnly | QFile::Text))
        {
            getLog()->printLn(LogTag::Error, QString("Failed to load default 404 page!"));
            return false;
        }
        else
        {
            QTextStream in(&notFoundPageFile);
            in.setCodec("UTF-8");
            m_notFoundPageResponse.setContent(in.readAll());
            m_notFoundPageResponse.setHeader("Content-Type", "text/html;charset=UTF-8");
        }

        return true;
    }

    //////////////////////////////////////////////////////////////////////////////

    const Response& Server::getNotFoundPageResponse() const
    {
        return m_notFoundPageResponse;
    }

    //////////////////////////////////////////////////////////////////////////////

}
