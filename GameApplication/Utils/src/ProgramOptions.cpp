#include "ProgramOptions.h"

ostream& operator<<(std::ostream& os, ProgramOptions& options)
{
    auto begin=options.begin();
    auto end=options.end();
    for(auto iter=begin;iter!=end;++iter)
    {
      os<<iter->first<<" = "<<iter->second<<" ";
    }
    return os;
}

ProgramOptions::ProgramOptions()
{

}

ProgramOptions::~ProgramOptions()
{
  m_Options.clear();
}

void ProgramOptions::addOption(const string& name, const string& value)
{
  m_Options[name]=value;
}

const string& ProgramOptions::getOption(const string& name)
{
  return m_Options[name];
}

float ProgramOptions::getOptionAsFloat(const string& name)
{
  return stof(m_Options[name]);
}

int ProgramOptions::getOptionAsInt(const string& name)
{
    return stoi(m_Options[name]);
}

bool ProgramOptions::getOptionAsBool(const string& name)
{
    return (bool)stoi(m_Options[name]);
}
