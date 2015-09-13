#ifndef STRUCTORUTIL_HH_
#define STRUCTORUTIL_HH_

#include <string>
#include <vector>

#include "Field.hh"
#include "Structure.hh"

using namespace std;

class StructorUtil {
public:

	StructorUtil();
	virtual ~StructorUtil();

	void pushField(Field field);

	vector<Field> pullFields();

	void printFields();

	void clearFields();

private:
	vector<Structure> _Structs;
	vector<Field>  _Fields;
};

#endif /* STRUCTORUTIL_HH_ */
