#ifndef _XML_OPTIONS_PARSER_H
#define _XML_OPTIONS_PARSER_H

#include "OptionParser.h"

#include <string>

using namespace std;

class XMLOptionsParser:public OptionParser
{
public:
  XMLOptionsParser(const string& filename);
  ~XMLOptionsParser();

  void parse(ProgramOptions &options);
private:
  string m_Filename;
};

#endif
