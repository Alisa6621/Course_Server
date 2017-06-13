#pragma once

#include <map>
#include <QtCore>

namespace httpserver
{

enum class ConfigValue
{
    Port,
    NotFoundPageLocation,
    ServerRoot,
};

class Config
{
public:
    Config();
    ~Config() = default;

    bool load();

    quint16 getPort() const { return m_port; }
    QString getRootLocation() const { return m_rootLocation; }
    QString getNotFoundPageLocation() const { return m_notFoundPageLocation; }

private:
    bool parseInt(const QString& textValue, int& value) const;

private:
    static std::map<QString, ConfigValue> s_configDeclarations;

    quint16 m_port = 0;
    QString m_rootLocation;
    QString m_notFoundPageLocation;
};

}
