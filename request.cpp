#include "request.h"

#include <iostream>
#include <QStringList>

namespace httpserver
{

//////////////////////////////////////////////////////////////////////////////

std::map<QString, RequestMethod> Request::s_requestMethodsMapping =
{
    std::make_pair("get", RequestMethod::Get),
    std::make_pair("post", RequestMethod::Post),
    std::make_pair("head", RequestMethod::Head),
    std::make_pair("put", RequestMethod::Put),
    std::make_pair("delete", RequestMethod::Delete),
    std::make_pair("connect", RequestMethod::Connect),
    std::make_pair("options", RequestMethod::Options),
    std::make_pair("trace", RequestMethod::Trace),
    std::make_pair("undefined", RequestMethod::Undefined)
};

//////////////////////////////////////////////////////////////////////////////

Request::Request()
{

}

//////////////////////////////////////////////////////////////////////////////

Request::Request(const QByteArray& requestData)
{
    parse(requestData);
}

//////////////////////////////////////////////////////////////////////////////

Request::~Request()
{

}

//////////////////////////////////////////////////////////////////////////////

void Request::parse(const QByteArray& requestData)
{
    m_requestText = QString::fromUtf8(requestData);
    QStringList requestLines = m_requestText.split("\r\n");

    if (requestLines.size() >= 1)
    {
        QString headerLine = requestLines[0];
        QStringList headerParts = headerLine.split(' ');

        if (headerParts.size() >= 2)
        {
            m_method = requestMethodFromString(headerParts[0].toLower());
            m_uri = headerParts[1];
        }
        else
        {
            std::cerr << "Failed to parse request header!" << std::endl;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

RequestMethod Request::requestMethodFromString(const QString& str) const
{
    auto mappingIt = s_requestMethodsMapping.find(str);
    return (mappingIt != s_requestMethodsMapping.end()) ? mappingIt->second : RequestMethod::Undefined;
}

//////////////////////////////////////////////////////////////////////////////

QString Request::getMethodStr(RequestMethod method) const
{
    for (auto pair : s_requestMethodsMapping)
    {
        if (pair.second == method)
        {
            return pair.first;
        }
    }

    return QString();
}

//////////////////////////////////////////////////////////////////////////////

}
