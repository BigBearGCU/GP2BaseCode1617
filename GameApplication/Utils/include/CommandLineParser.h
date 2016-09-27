#ifndef _COMMAND_LINE_PARSER_H
#define _COMMAND_LINE_PARSER_H

#include "OptionParser.h"

#include <vector>

using namespace std;

class CommandLineParser:public OptionParser
{
public:
  CommandLineParser(int argc,char * argv[]);
  ~CommandLineParser();

  void parse(ProgramOptions &options);
private:
  vector<string> m_CommandArguments;
};
#endif
