#pragma once

#include <map>
#include <QByteArray>
#include <QString>

namespace httpserver
{

enum class RequestMethod
{
    Get,
    Head,
    Post,
    Put,
    Delete,
    Connect,
    Options,
    Trace,
    Undefined
};

class Request
{
public:
    Request();
    Request(const QByteArray& requestData);
    ~Request();

    void parse(const QByteArray& requestData);

    QString getText() const { return m_requestText; }
    QString getUri() const { return m_uri; }
    RequestMethod getMethod() const { return m_method; }

    RequestMethod requestMethodFromString(const QString& str) const;
    QString getMethodStr(RequestMethod method) const;

private:
    RequestMethod m_method;
    QString m_requestText;
    QString m_uri;

    static std::map<QString, RequestMethod> s_requestMethodsMapping;
};

}
