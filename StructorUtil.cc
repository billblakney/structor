#include "StructorUtil.hh"

#include <iostream>

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

