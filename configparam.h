#pragma once

namespace httpserver
{

//////////////////////////////////////////////////////////////////////////////

class BaseConfig
{
public:
    virtual bool parse(QString textValue) = 0;
};

//////////////////////////////////////////////////////////////////////////////

template <typename T>
class ConfigParam : public BaseConfig
{
public:
    ConfigParam(T& ref) : m_ref(ref) {}

private:
    T& m_ref;
};

//////////////////////////////////////////////////////////////////////////////

class IntParam : public ConfigParam<int>
{
public:
    virtual bool parse(QString textValue) override
    {
        bool isOk;
        m_ref = textValue.toInt(&isOk);
        return isOk;
    }
};

//////////////////////////////////////////////////////////////////////////////

class StringParam : public ConfigParam<QString>
{
public:
    virtual bool parse(QString textValue) override
    {
        m_ref = textValue;
        return true;
    }
};

//////////////////////////////////////////////////////////////////////////////

}
