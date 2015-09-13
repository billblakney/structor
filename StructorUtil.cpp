#include <iostream>
#include "StructorUtil.h"

StructorUtil::StructorUtil() {
}

StructorUtil::~StructorUtil() {
}

void StructorUtil::addField(Field field) {
	_Fields.push_back(field);
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

