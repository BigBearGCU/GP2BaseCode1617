#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc,char * argv[])
{
  //skip first arg as always app name
  for (int i=1;i<argc;++i)
  {
    m_CommandArguments.push_back(string(argv[i]));
    cout<<"Commands "<<m_CommandArguments[i-1]<<endl;
  }
}

CommandLineParser::~CommandLineParser()
{
  m_CommandArguments.clear();
}

//command line arguments will be value key pairs
//seperated by '=', so we split and then add to our
//program options structure
void CommandLineParser::parse(ProgramOptions &options)
{
  auto begin=m_CommandArguments.begin();
  auto end=m_CommandArguments.end();
  string key;
  string value;
  int splitPos;
  for(auto iter=begin;iter!=end;iter++)
  {
    splitPos=iter->find('=');
    key=iter->substr(0,splitPos);
    value=iter->substr(splitPos+1,iter->length());
    cout<<"Commands out "<<key<<" "<<value<<endl;
    options.addOption(key,value);

  }
}
