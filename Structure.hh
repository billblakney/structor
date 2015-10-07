#ifndef STRUCTURE_HH_
#define STRUCTURE_HH_

#include <string>
#include <map>
#include <vector>
#include "Field.hh"

class StructorUtil;

class Structure
{
public:

  Structure();

  Structure(std::string aName);

  virtual ~Structure();

  void addFields(vector<Field> aFields);

  void addField(Field aField);

  void postProcess(StructorUtil *aStructUtil,int aLevel = 0);

  std::string toString();

  std::string _Name;

  vector<Field> _Fields;
};

#endif /* STRUCTURE_HH_ */
