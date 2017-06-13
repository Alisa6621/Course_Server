#include "log.h"

namespace httpserver
{

//////////////////////////////////////////////////////////////////////////////

Log::Log()
{
    m_file.reset(new QFile("logs/log.txt"));
    m_file->open(QIODevice::WriteOnly);
}

//////////////////////////////////////////////////////////////////////////////

Log::~Log()
{
    m_file->flush();
    m_file->close();
}

//////////////////////////////////////////////////////////////////////////////

void Log::print(LogTag tag, QString& string)
{
    printTag(tag);
    m_file->write(string.toUtf8().constData());

    m_file->flush();
}

//////////////////////////////////////////////////////////////////////////////

void Log::printLn(LogTag tag, QString& string)
{
    printTag(tag);
    m_file->write(string.toUtf8().constData());
    m_file->write("\r\n");

    m_file->flush();
}

//////////////////////////////////////////////////////////////////////////////

void Log::printTag(LogTag tag)
{
    switch (tag)
    {
    case LogTag::Info:
        m_file->write("[INFO] ");
        break;
    case LogTag::Warning:
        m_file->write("[WARNING] ");
        break;
    case LogTag::Error:
        m_file->write("[ERROR] ");
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////

}
