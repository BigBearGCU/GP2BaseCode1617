#include "Log.h"
#include "clock.h"

//enumeration types (both scoped and unscoped) can have overloaded operators
ostream& operator<<(std::ostream& os, LogLevel level)
{
    switch(level)
    {
        case INFO   : os << "INFO";    break;
        case WARNING: os << "WARNING"; break;
        case ERROR : os << "ERROR";  break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}

Log::Log()
{
  m_CurrentLevel = (unsigned int)(INFO|WARNING|ERROR);
  m_MessageBufferSize=10;
}

Log::~Log()
{
  close();
}

void Log::create(const string& filename)
{
  m_FileStream.open(filename.c_str());
  cout<<"Log Created on "<<getLocalTimeStr()<<endl;
  m_FileStream<<"Log Created on "<<getLocalTimeStr()<<endl;
}

void Log::write(unsigned int level,const char* format, ...)
{
  //need a mutex here
  //filter out messages we are not interested in
  if ((level & m_CurrentLevel)==0)
  {
    char    buffer [1024];
    va_list va;
    va_start(va,format);
    vsnprintf (buffer,
               1024,
               format,
               va);
    va_end (va);

    stringstream ss;
    ss<<(LogLevel)level<<" "<<getLocalTimeStr()<<" "<<buffer<<endl;
    cout<<ss.str();
    m_LogMessages.push(ss.str());
    ss.clear();
    if (m_LogMessages.size()>=10)
    {
      flush();
    }
  }
}

void Log::flush()
{
  //mutex here
  while(!m_LogMessages.empty())
  {
    m_FileStream<<m_LogMessages.front();
    m_LogMessages.pop();
  }

  m_FileStream.flush();
}

void Log::close()
{
  flush();
  m_FileStream.close();
}

void Log::setLogLevel(unsigned int level)
{
  m_CurrentLevel=level;
}
