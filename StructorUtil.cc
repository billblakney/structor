#include "StructorUtil.hh"

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
	for( auto field: _Fields ){
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
      std::string tFieldName = it->_Name;
      std::string tFieldType = it->_Type;
      std::string tFieldString = aPrefix + "." + tFieldName;
      std::string tFieldDotString = getDotString(tFieldType,tFieldString);
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
