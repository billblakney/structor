#include <iostream>
#include "StructorUtil.h"

StructorUtil::StructorUtil() {
}

StructorUtil::~StructorUtil() {
}

void StructorUtil::addField(Field field) {
	fields.push_back(field);
}

void StructorUtil::clearFields() {
	fields.clear();
}

void StructorUtil::printFields() {
	cout << "FIELDS:" << endl;
	for( auto field: fields ){
		cout << "field: " << field.toString() << endl;
	}
}

