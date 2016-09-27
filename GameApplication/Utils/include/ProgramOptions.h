#ifndef _PROGRAM_OPTIONS_H
#define _PROGRAM_OPTIONS_H

#include <string>
#include <map>
#include <iostream>

using namespace std;

class ProgramOptions
{
public:
  ProgramOptions();
  ~ProgramOptions();

  void addOption(const string& name, const string& value);
  const string& getOption(const string& name);
  float getOptionAsFloat(const string& name);
  int getOptionAsInt(const string& name);
  bool getOptionAsBool(const string& name);
  map<string,string>::iterator begin()
  {
    return m_Options.begin();
  };

  map<string,string>::iterator end()
  {
    return m_Options.end();
  };

  friend ostream& operator<<(ostream& os, ProgramOptions& options);
private:
  map<string,string> m_Options;
};
#endif
