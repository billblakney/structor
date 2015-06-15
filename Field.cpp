#include <sstream>
#include "Field.h"

Field::Field(string aType, string aName, int aIsPointer)
{
	_Type = aType;
	_Name = aName;
	_IsPointer = aIsPointer ? true : false;
}

Field::~Field()
{
}

string Field::toString()
{
	stringstream str;
	str << "type: " << _Type << ", "
		<< "name: " << _Name << ", "
		<< "isPointer: " << _IsPointer;
	return str.str();
}
