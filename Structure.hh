#ifndef STRUCTURE_HH_
#define STRUCTURE_HH_

#include <string>

class Structure
{
public:
  Structure();
  Structure(std::string aName);
  virtual ~Structure();
  std::string _Name;
};

#endif /* STRUCTURE_HH_ */
