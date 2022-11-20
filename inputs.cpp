#include "inputs.h"
#include <iostream>

// using constructor to manage all inputs
Inputs::Inputs() {
  std::cout << "\n High or low pass?: (h / l)\n ";
  std::cin >> type;

  std::cout
      << "\n Buterrworth or Chebyshev(0.5Db)OR Chebyshev(2dB)?:(1/2/3)\n ";
  std::cin >> design;

  std::string p;
  std::cout << "\n How many poles are needed?: (2/4/6)\n ";
  std::cin >> p;
  poles = stoi(p); // converting to int

  std::string f;
  std::cout << "\n What is your cut-off frequency?: \n";
  std::cin >> f;
  fc = stoi(f); // converting to int
}

std::string Inputs::get_type() { return (type); }
std::string Inputs::get_design() { return (design); }
int Inputs::get_poles() { return (poles); }
int Inputs::get_fc() { return (fc); }
