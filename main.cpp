#include "inputs.h"
#include <iostream>
#define PI 3.14159265
#include <array>    // mention in code
#include <string.h> //

void active_filter_config();
// double butterworth(int poles, int fc);
// bool test_sum(double a, double b, double expected); //unit test
// int run_sum_tests();
std::array<double, 5> Butterworth(int poles, int fc);

int main() {

  std::string input;
  std::cout << "\n*******Filter Calculator*******\n";
  std::cout << "\nAre you designing a activer filer?(y/n)\n ";
  std::cin >> input;

  // run_sum_tests();
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
    std::array<double, 5> arr;
    arr = Butterworth(poles, fc);
    std::cout << "\n " << arr[2] << "\n "; // testing outputs
    std::cout << "\n " << arr[1] << "\n "; // testing outputs
    std::cout << "\n " << arr[0] << "\n "; // testing outputs

    break;
  case 2:
    // chebyshev_half();
    break;
  case 3:
    // chebyshev_two();
    break;
  }
}

std::array<double, 5> Butterworth(int poles, int fc) {
  // initialising rb and cap values
  int scale = 10;
  double rb = 10000;
  double c = 0.00000001;
  std::array<double, 5> ra;
  int i = 0;
  int z = 3;
  // initialsing k values for calculating rb
  float array[3][3] = {{1.586, 0, 0}, {1.152, 2.325, 0}, {1.068, 1.586, 2.483}};
  int stages = (poles / 2) - 1;
  // iterating throug to select required K value
  for (int e = 0; e < 3; e++) {
    // setting calculated value equal to array spot to be returned
    ra[i] = rb * (array[stages][e] - 1);
    i = i + 1;
    // std::cout<< "\n "<< ra[i]<< "\n "; testing output
  }
  // converting f to a double
  for (int e = 0; e < stages; e++) {
    double f = fc;
    double rc = (1 / (f * 2 * PI));
    double r = rc / c;
    ra[z] = r;
    z = z + 1;
  }

  // std::cout << "\n " << ra << "\n "; inital testing
  // std::cout << "\n " << r << "\n ";inital testing

  return (ra);
};

// CODE IS FROM https://elec2645.github.io/106/testing.html

// // Function to test combinations
// bool test_sum(double a, double b, double expected) {
//   double val = butterworth(a, b); // calc value and compare to expected
//   std::string s = std::to_string(val);
//   std::string s1 = std::to_string(val);
//   if (s == s1) {
//     std::cout << "passed\n";
//     return true;
//   } else {
//     std::cout << "FAILED! " << val << " (expecting " << expected << ").\n";
//     return false;
//   }
// }

// // function to run the tests
// int run_sum_tests() {
//   std::cout << "\nTesting sum()...\n" << std::endl;
//   // initialise counter for number of tests passed
//   int passed = 0;
//   // do various tests
//   if (test_sum(2, 10000, 1591.55))
//     passed++;
//   if (test_sum(2, 80000, 198.944))
//     passed++;
//   if (test_sum(2, 900, 17683.883))
//     passed++;
//   std::cout << "\nsum() passed " << passed << " tests.\n";
//   return passed;
// }