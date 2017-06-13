#pragma once

#include <map>
#include <QByteArray>
#include <QString>

namespace httpserver
{

struct HttpStatus
{
    enum Code : int
    {
        Success = 200,
        NotFound = 404,
    };

    static QString getSymbolicName(Code code)
    {
        switch (code)
        {
        case Code::Success:
            return "OK";
        case Code::NotFound:
            return "Not Found";
        default:
            return QString();
        }
    }
};

class Response
{
public:
    Response() = default;
    ~Response() = default;

    QByteArray construct();

    void setStatus(HttpStatus::Code statusCode);
    void setHeader(const QString& name, const QString& value);
    void setContent(const QByteArray& content);
    void setContent(const QString& content);

private:
    HttpStatus::Code m_statusCode;
    std::map<QString, QString> m_headers;
    QByteArray m_content;
};

}
