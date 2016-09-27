#ifndef _OPTION_PARSER_H
#define _OPTION_PARSER_H

#include "ProgramOptions.h"

class OptionParser
{
public:
  ~OptionParser(){};

  virtual void parse(ProgramOptions &options)=0;
};

#endif
