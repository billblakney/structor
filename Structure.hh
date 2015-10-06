#ifndef STRUCTURE_HH_
#define STRUCTURE_HH_

#include <string>
#include <vector>
#include "Field.hh"

class Structure
{
public:

  Structure();

  Structure(std::string aName);

  virtual ~Structure();

  void addFields(vector<Field> aFields);

  void addField(Field aField);

  void postProcess();

  std::string toString();

  std::string _Name;

  vector<Field> _Fields;
};

#endif /* STRUCTURE_HH_ */
