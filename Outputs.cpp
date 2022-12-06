#include "Outputs.h"
Outputs::Outputs(std::vector<double> rc, std::vector<double> ra)
    : Inputs{}, rc{rc}, ra {ra} {};

// //mutators
void Outputs::set_rc(std::vector<double> rc) { rc = rc; }
void Outputs::set_ra(std::vector<double> ra) { ra = ra; }

// accessors
std::vector<double> Outputs::get_rc() { return (rc); }
std::vector<double> Outputs::get_ra() { return (ra); }