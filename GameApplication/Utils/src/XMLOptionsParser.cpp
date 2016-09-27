#include "XMLOptionsParser.h"
#include "tinyxml2.h"
#include "Log.h"

using namespace tinyxml2;

XMLOptionsParser::XMLOptionsParser(const string& filename)
{
  m_Filename=filename;
}

XMLOptionsParser::~XMLOptionsParser()
{

}

void XMLOptionsParser::parse(ProgramOptions &options)
{
  //parse xml file, keep element name and combine with attribute name for key
  //value comes from atrribute value
  LOG(INFO,"Reading XML Document %s",m_Filename.c_str());
	XMLDocument doc;
  if (doc.LoadFile(m_Filename.c_str())!=XML_NO_ERROR)
  {
    LOG(ERROR,"Can't parse XML %s",doc.GetErrorStr1());
    return;
  }

  XMLHandle hDoc(&doc);
  XMLElement* pCurrentElement;
  const XMLAttribute* pCurrentAttribute;
  string currentKey;
  string currentValue;
  XMLHandle hRoot(0);

  pCurrentElement = hDoc.FirstChildElement().ToElement();
  if (!pCurrentElement)
  {
    LOG(ERROR,"%s","Can't grab root of XML");
    return;
  }

  LOG(INFO,"Root Element %s",pCurrentElement->Name());
  //We should always ignore root
  hRoot=XMLHandle(pCurrentElement);
  //iterate through all elements
  for( pCurrentElement = pCurrentElement->FirstChildElement(); pCurrentElement;
    pCurrentElement = pCurrentElement->NextSiblingElement() )
  {
    //add all attributes
    for (pCurrentAttribute=pCurrentElement->FirstAttribute();pCurrentAttribute;
      pCurrentAttribute=pCurrentAttribute->Next())
    {
      currentKey.clear();
      currentValue.clear();
      currentKey=string(string(pCurrentElement->Value())+string(pCurrentAttribute->Name()));
	  currentValue = pCurrentAttribute->Value();


      options.addOption(currentKey,currentValue);
    }
  }
}
