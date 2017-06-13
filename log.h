#pragma once

#include <memory>
#include <QFile>

namespace httpserver
{

enum class LogTag
{
    Info,
    Warning,
    Error
};

class Log
{
   friend class Server;

public:
   ~Log();

    void print(LogTag tag, QString& string);
    void printLn(LogTag tag, QString& string);
    void printTag(LogTag tag);

private:
    Log();

private:
    std::unique_ptr<QFile> m_file;
};

using LogPtr = std::shared_ptr<Log>;

}
