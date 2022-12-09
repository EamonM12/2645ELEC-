#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "inputs.h"
#include <string>
#include <vector>

class Outputs : public Inputs {
public:
  Outputs(std::string type, std::string design, int poles, double fc,
          std::vector<double> rc, std::vector<double> ra);

  // mutators to access all values
  void set_ra(std::vector<double> ra);
  void set_rc(std::vector<double> rc);

  // accessors
  std::vector<double> get_ra();
  std::vector<double> get_rc();

private:
  // resistor values
  std::vector<double> rc;
  std::vector<double> ra;
};

#endif