#ifndef STRUCTORUTIL_H_
#define STRUCTORUTIL_H_

#include <string>
#include <vector>
#include "Field.h"

using namespace std;

class StructorUtil {
public:
	class Struct {
		string name;
	};

	StructorUtil();
	virtual ~StructorUtil();

	void addField(Field field);
	void printFields();
	void clearFields();
private:
	vector<Struct> _Structs;
	vector<Field>  _Fields;
};

#endif /* STRUCTORUTIL_H_ */
