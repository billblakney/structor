#include <iterator>
#include <sstream>
#include "Structure.hh"

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

void Structure::postProcess()
{
  vector<Field>::iterator tIter;
  for (tIter = _Fields.begin(); tIter != _Fields.end(); tIter++)
  {

  }
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
