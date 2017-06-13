#include "response.h"

namespace httpserver
{

//////////////////////////////////////////////////////////////////////////////

QByteArray Response::construct()
{
    QByteArray responseBody;

    responseBody.append(QString("HTTP/1.1 %1 %2\r\n").arg(m_statusCode).arg(HttpStatus::getSymbolicName(m_statusCode)));

    for (auto header : m_headers)
    {
        responseBody.append(QString("%1: %2\r\n").arg(header.first, header.second));
    }

    //добавляем контент
    responseBody.append(QString("Content-Length: %1\r\n").arg(m_content.size()));
    responseBody.append("\r\n");
    responseBody.append(m_content);

    return responseBody;
}

//////////////////////////////////////////////////////////////////////////////

void Response::setStatus(HttpStatus::Code statusCode)
{
    m_statusCode = statusCode;  //установка статуса ответа(200, 404 и т.д.)
}

//////////////////////////////////////////////////////////////////////////////

void Response::setHeader(const QString& name, const QString& value)
{
    m_headers.insert_or_assign(name, value);
}

//////////////////////////////////////////////////////////////////////////////

void Response::setContent(const QByteArray& content)
{
    m_content = content;
}

//////////////////////////////////////////////////////////////////////////////

void Response::setContent(const QString& content)
{
    m_content = content.toUtf8();
}

//////////////////////////////////////////////////////////////////////////////

}
