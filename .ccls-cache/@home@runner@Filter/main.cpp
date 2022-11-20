#include "inputs.h"
#include <iostream>

void active_filter_config();
void butterworth(int poles, int fc);

int main() {

  std::string input;
  std::cout << "\n*******Filter Calculator*******\n";
  std::cout << "\nAre you designing a activer filer?(y/n)\n ";
  std::cin >> input;

  if (input == "y") {
    active_filter_config();
  } else if (input == "n") {

  } else {
    std::cout << "Inavlid input";
  }
}

void active_filter_config() {

  // creating constructor to create object with all inputs on it
  Inputs input;
  // getting desgin(butterworth / chebyshev(0.5dB/2db))
  int design = stoi(input.get_design());
  // std::cout << design; // Testing accessor for design
  // getting type(h/l)
  std::string type = input.get_type();
  // std::cout << type; // Testing accessor for type
  int poles = input.get_poles();
  // std::cout << poles; // Testing accessor for poles
  int fc = input.get_fc();
  // std::cout << poles; // Testing accessor for poles

  // switch method to choose between designs
  switch (design) {

  case 1:
    // std::cout
    // << design; // printing values out to test butterworth func is called
    butterworth(poles, fc);

    break;
  case 2:
    // chebyshev_half();
    break;
  case 3:
    // chebyshev_two();
    break;
  }
}

void butterworth(int poles, int fc) {
  // initialising rb and cap values
  float rb = 10000;
  float c = 0.000000010;
  float ra;
  // initialsing k values for calculating rb
  float array[3][3] = {{1.586, 0, 0}, {1.152, 2.325, 0}, {1.068, 1.586, 2.483}};
  int stages = poles / 2;
  for (int i = 0; i < stages; i++) {
    ra = rb * (array[0][i] - 1);

    ;
  }
};

// // Function to test combinations
// bool test_sum(std::string a, std::string b, std::string c, int expected) {
//   int val = active_filter(a, b); // calc value and compare to expected
//   if (val == expected) {
//     std::cout << "passed\n";
//     return true;
//   } else {
//     std::cout << "FAILED! " << val << " (expecting " << expected << ").\n";
//     return false;
//   }
// }