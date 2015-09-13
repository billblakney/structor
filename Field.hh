#ifndef FIELD_HH_
#define FIELD_HH_

#include <string>

using namespace std;

/**
 * A Field class instance represents a field of a structure.
 */

class Field {
public:
	bool _IsPointer;
	string _Type;
	string _Name;

	Field(string aType, string aName, int aIsPointer);
	virtual ~Field();

	string toString();
};

#endif /* FIELD_HH_ */
