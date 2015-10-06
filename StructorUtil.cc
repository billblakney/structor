#include "StructorUtil.hh"

#ifndef C11
#include <iterator>
#include <stdio.h>
#endif
#include <iostream>
#include <sstream>

StructorUtil::StructorUtil() {
}

StructorUtil::~StructorUtil() {
}

void StructorUtil::pushField(Field field) {
	_Fields.push_back(field);
}

vector<Field> StructorUtil::pullFields()
{
  return _Fields;
}

void StructorUtil::clearFields() {
	_Fields.clear();
}

void StructorUtil::printFields() {
	cout << "FIELDS:" << endl;
#ifdef C11
	for( auto field: _Fields ){
#else
	vector<Field>::iterator tIter;
	for( tIter = _Fields.begin(); tIter != _Fields.end(); tIter++ ){
		Field field = *tIter;
#endif
		cout << "field: " << field.toString() << endl;
	}
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void StructorUtil::onMatch(const char *aRuleName)
{
   static int _debug = 0;
   if( _debug )
      cout << "matched: " << aRuleName << endl;;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void StructorUtil::onField(string *aName,string *aType,int aIsPointer)
{
   static int _debug = 0;
   Field tField(*aName,*aType,aIsPointer);
   pushField(tField);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void StructorUtil::onStruct(std::string *aStructName)
{
   static int _debug = 0;

   Structure *tStructure = new Structure(*aStructName);

   tStructure->addFields(pullFields());
   clearFields();

   if( _debug )
      printf("struct: %s\n",tStructure->toString().c_str());

   _Structs[*aStructName] = tStructure;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string StructorUtil::getDotString(std::string aName,std::string aPrefix)
{
  stringstream tReturn;

  map<std::string,Structure *>::iterator tStructIter;
  tStructIter = _Structs.find(aName);

  if( tStructIter != _Structs.end() )
  {
    Structure *tStructure = tStructIter->second;
    vector<Field>::iterator it;
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
  }

  return tReturn.str();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void StructorUtil::postProcess()
{
  std::string tCarReportType("CONTACT_ATTRIBUTES_REPORT_T");

  map<std::string,Structure *>::iterator it;
  it = _Structs.find(tCarReportType);
  if( it == _Structs.end() )
  {
    cout << "couldn't find " << tCarReportType;
  }
  else
  {
    cout << "FOUND " << tCarReportType;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void StructorUtil::printSummary()
{
   static int _debug = 1;
   map<std::string,Structure *>::iterator it;
#if 0
   for( it = _Structs.begin() ; it != _Structs.end(); it++ ){
   	  Structure *tStruct = it->second;
      printf("struct: %s\n",tStruct->toString().c_str());
   }
#endif
   for( it = _Structs.begin() ; it != _Structs.end(); it++ ){
   	  Structure *tStruct = it->second;
      cout << "struct: " << tStruct->_Name << endl;
      cout << getDotString(tStruct->_Name,"aStruct") << endl;
   }
}
