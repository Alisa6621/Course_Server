#include "config.h"

#include <iostream>
#include <QDomDocument>

namespace httpserver
{

QString configFileLocation = "config.xml";

std::map<QString, ConfigValue> Config::s_configDeclarations =
{
    std::make_pair("port", ConfigValue::Port),
    std::make_pair("not_found_page_location", ConfigValue::NotFoundPageLocation),
    std::make_pair("server_root", ConfigValue::ServerRoot),
};

//////////////////////////////////////////////////////////////////////////////

Config::Config()
{

}

//////////////////////////////////////////////////////////////////////////////

bool Config::load()
{
    QFile configFile(configFileLocation);
    QDomDocument document;
    if (!configFile.open(QIODevice::ReadOnly) || !document.setContent(&configFile))
        return false;

    auto root = document.documentElement();
    auto childNodes = root.childNodes();
    for (int i = 0, sz = childNodes.count(); i < sz; i++)
    {
        const auto& configNode = childNodes.at(i).toElement();
        QString name = configNode.attribute("name");
        QString value = configNode.attribute("value");

        auto configDeclaration = s_configDeclarations.find(name);
        if (configDeclaration == s_configDeclarations.end())
            return false;

        ConfigValue configType = configDeclaration->second;
        switch (configType)
        {
        case ConfigValue::Port:
            {
                int port;
                if (!parseInt(value, port))
                    return false;

                m_port = port;
            }
            break;
        case ConfigValue::NotFoundPageLocation:
            m_notFoundPageLocation = value;
            break;
        case ConfigValue::ServerRoot:
            m_rootLocation = value;
            break;
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////

bool Config::parseInt(const QString& textValue, int& value) const
{
    bool isOk;
    value = textValue.toInt(&isOk);
    return isOk;
}

//////////////////////////////////////////////////////////////////////////////

}
