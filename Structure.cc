#include <iostream>
#include <iterator>
#include <sstream>
#include <boost/regex.hpp>
#include "Structure.hh"
#include "StructorUtil.hh"

Structure::Structure()
{
}


Structure::Structure(std::string aName)
{
  _Name = aName;
}

Structure::~Structure()
{
}

void Structure::addFields(vector<Field> aFields)
{
  _Fields = aFields;
}

void Structure::addField(Field aField)
{
  _Fields.push_back(aField);
}

//TODO deep enough? replace generically?
static std::string blanks[] = {
    "",
    "  ",
    "    ",
    "      ",
    "        ",
    "          ",
    "            ",
    "              ",
    "                ",
    "                  ",
};

void Structure::postProcess(StructorUtil *aStructUtil,int aLevel)
//void Structure::postProcess(std::map<std::string,Structure *> &aStructMap)
{
  boost::regex array_size_regex("^([a-zA-Z]+)_size$");

  if (aLevel == 0)
  {
    std::cout << "root node: " << _Name << std::endl;
  }

  vector<Field>::iterator tIter;
  for (tIter = _Fields.begin(); tIter != _Fields.end(); tIter++)
  {
    boost::match_results<std::string::const_iterator> what;

    // is array size line
    if (boost::regex_match(tIter->_Name,array_size_regex))
    {
      std::string tName = what[1];
      std::cout << blanks[aLevel];
      std::cout << "array size entry: "
          << tIter->_Type << ":" << tIter->_Name << std::endl;
    }
    else if (tIter->_IsPointer)
    {
      // is primitive pointer
      if (aStructUtil->isPrimitive(tIter->_Type))
      {
      std::cout << blanks[aLevel];
        std::cout << "primitive array node: "
            << tIter->_Type << ":" << tIter->_Name << std::endl;
      }
      // is struct pointer
      else
      {
      std::cout << blanks[aLevel];
        std::cout << "struct array node: "
            << tIter->_Type << ":" << tIter->_Name << std::endl;
        Structure *tStruct = aStructUtil->getStructure(tIter->_Type);
        if (tStruct != NULL)
        {
          tStruct->postProcess(aStructUtil,++aLevel);
          --aLevel;
        }
      }
    }
    // is struct
    else if (!aStructUtil->isPrimitive(tIter->_Type))
    {
      std::cout << blanks[aLevel];
      std::cout << "struct node: "
          << tIter->_Type << ":" << tIter->_Name << std::endl;
      Structure *tStruct = aStructUtil->getStructure(tIter->_Type);
      if (tStruct != NULL)
      {
        tStruct->postProcess(aStructUtil,++aLevel);
        --aLevel;
      }
      else
      {
      std::cout << blanks[aLevel];
        std::cout << "ERROR: can't find struct " << tIter->_Name << std::endl;
      }
    }
    // is primitive
    else
    {
      std::cout << blanks[aLevel];
      std::cout << "primitive node: "
          << tIter->_Type << ":" << tIter->_Name << std::endl;
    }
  }
#if 0
  for( it = tStructure->_Fields.begin(); it != tStructure->_Fields.end(); it++)
  {
    std::string tName = it->_Name;
    std::string tType = it->_Type;
    std::string tFieldString = aPrefix + "." + tName;
    std::string tFieldDotString = getDotString(tType,tFieldString);
    if( tFieldDotString.length() )
    {
      tReturn << tFieldDotString;
    }
    else
    {
      tReturn << tFieldString << endl;
    }
  }
#endif
}

std::string Structure::toString()
{
  stringstream tStream;

  tStream << _Name << std::endl;
  vector<Field>::iterator it;
  for( it = _Fields.begin(); it != _Fields.end(); it++ )
  {
    tStream << it->toString() << std::endl;
  }

  return tStream.str();
}
