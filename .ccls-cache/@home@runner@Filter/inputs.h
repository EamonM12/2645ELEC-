#ifndef INPUTS_H
#define INPUTS_H
#include <iostream>

// creating a class to allow inputs to be collected togther in one object

class Inputs {
public:
  Inputs();
  Inputs(std::string type, std::string design, std::string poles,
         std::string fc);
  // accessors to allow for user options
  std::string get_type();
  std::string get_design();
  std::string get_poles();
  std::string get_fc();

private:
  // member variables for all the different combinations
  std::string type;
  std::string design;
  std::string poles;
  std::string fc;
};

#endif