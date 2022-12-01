#include "inputs.h"
#include <iostream>
#define PI 3.14159265
#include <algorithm>
#include <array>
#include <cmath>
#include <string.h>

void active_filter_config();
std::array<double, 6> Butterworth(int poles, int fc);
std::array<double, 6> Chebyshev(int poles, int fc, std::string type);

// bool test_sum(double a, double b, double expected); //unit test
// int run_sum_tests();
// bool test(double a, double b, std::array<double, 6> expected);
// int run_test();

int main() {

  std::string input;
  std::cout << "\n*******Filter Calculator*******\n";
  std::cout << "\nAre you designing a activer filer?(y/n)\n ";
  std::cin >> input;
  // run_test();
  if (input == "y") {
    active_filter_config();

  } else if (input == "n") {

  } else {
    std::cout << "Inavlid input";
  }
}

void active_filter_config() {
  std::array<double, 6> arr;

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

    arr = Butterworth(poles, fc);
    // std::cout << "\n " << arr[0] << "\n "; // testing outputs
    // std::cout << "\n " << arr[1] << "\n "; // testing outputs
    // std::cout << "\n " << arr[2] << "\n "; // testing outputs
    // std::cout << "\n " << arr[3] << "\n "; // testing outputs
    // std::cout << "\n " << arr[4] << "\n "; // testing outputs
    // std::cout << "\n " << arr[5] << "\n "; // testing outputs

    break;
  case 2:

    arr = Chebyshev(poles, fc, type);
    // std::cout << "\n " << arr[0] << "\n "; // testing outputs
    // std::cout << "\n " << arr[1] << "\n "; // testing outputs
    // std::cout << "\n " << arr[2] << "\n "; // testing outputs
    // std::cout << "\n " << arr[3] << "\n "; // testing outputs
    // std::cout << "\n " << arr[4] << "\n "; // testing outputs
    // std::cout << "\n " << arr[5] << "\n "; // testing outputs
    break;
  }
}
// function to calculate necessary values for a Butterworth Filter
std::array<double, 6> Butterworth(int poles, int fc) {
  // initialising rb and cap values and array to return
  double rb = 10000;
  double c = 0.00000001;
  std::array<double, 6> ra;
  int i = 0;
  int z = 3;
  // initialsing k values for calculating rb
  // 1st value corresponds to 1st stage - same for all values
  float array[3][3] = {{1.586, 0, 0}, {1.152, 2.325, 0}, {1.068, 1.586, 2.483}};
  int stages = (poles / 2) - 1;
  // iterating through to select required K value
  for (int e = 0; e < 3; e++) {
    // setting calculated value equal to array spot to be returned
    if (array[stages][e] == 0) {
      ra[i] = 0;
    } else {
      ra[i] = rb * (array[stages][e] - 1);
      i = i + 1;
    }
    // std::cout<< "\n "<< ra[i]<< "\n "; testing output
  }

  for (int e = 0; e < stages; e++) {
    // cacluating for all stages  and adding to array
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

// Fucntion to caluclate values for Chebyshev 0.5 or 2
std::array<double, 6> Chebyshev(int poles, int fc, std::string type) {

  // initialsing
  double rb = 10000;
  double c = 0.00000001;
  std::array<double, 6> arr;
  double array[3][3] = {};
  int i = 0;
  int z = 3;

  // array for both high low pass filters CN and K value
  // First 3 arrays are for lp and last 3 are for hp
  double cnl[3][3] = {{1.231, 0, 0}, {0.597, 1.031, 0}, {0.396, 0.768, 1.011}};
  double cnh[3][3] = {{0.812, 0, 0}, {1.675, 0.970, 0}, {2.525, 1.302, 0.989}};
  float k[3][3] = {{1.842, 0, 0}, {1.582, 2.660, 0}, {1.537, 2.448, 2.846}};

  // std::cout<< type; testing correct passing of values
  // if statement to determine what normalising factors to use
  if (type == "h") {
    std::copy(
        &cnh[0][0], &cnh[0][0] + 9,
        &array
            [0]
            [0]); // https://stackoverflow.com/questions/18709577/stdcopy-two-dimensional-array
  } // array is used to store values of cn depending on input
  if (type == "l") {

    std::copy(
        &cnl[0][0], &cnl[0][0] + 9,
        &array
            [0]
            [0]); // https://stackoverflow.com/questions/18709577/stdcopy-two-dimensional-array
    // std::cout << "\n " << "testing testing" << "\n "; // if statement works
  }

  // std::cout << "\n " << array[0][1] << "\n "; // testing outputs
  // std::cout << "\n " << array[2][1] << "\n "; // testing outputs
  // std::cout << "\n " << array[0][0] << "\n "; // testing outputs

  for (int e = 0; e < ((poles / 2)); e++) {
    // cacluating for all stages  and adding to

    if (array[poles / 2][e] == 0) {
      arr[i] = 0;
    } else {
      arr[i] = rb * (array[poles / 2][e] - 1);
      i = i + 1;
    }
    double f = fc;
    double cn =  array[poles / 2][e];
    // cacluation with normalsing factor included
    double rc = (1 / (f * 2 * PI *cn));
    std::cout << "\n " << rc << "\n "; // testing outputs

    double r = rc / c;
    std::cout << "\n " << r << "\n "; // testing outputs
    
    arr[z] = r;
    z = z + 1;

  }
  return (arr);
}
// Unit test code is from https://elec2645.github.io/106/testing.html

// // Function to test combinations
// bool test(double a, double b, std::array<double, 6> expected) {
//   std::array<double, 6> arr;
//   arr = Butterworth(a, b);
//   double s = arr[0];
//   int count = 0;
//   // for loop to check all values of the returned array
//   for (int i = 0; i < 6; i++) {
//     double s = round(arr[i]);
//     double s1 = round(expected[i]);

//     if (s1 == s) {
//       // count to ensure all values in array are correct
//       count = count + 1;

//     }
//   }

//   if (count == 5) {
//     std::cout << "passed\n";
//     return true;
//   } else {
//     // print all expected values for comparison
//     for (int e = 0; e < 6; e++) {
//       std::cout << "FAILED! "
//                 <<" (expecting " << expected[e] << ").\n";
//     }
//     return false;
//   }
// }

// // function to run the tests
// int run_test() {
//   std::cout << "\nTesting sum()...\n" << std::endl;
//   // initialise counter for number of tests passed
//   int passed = 0;
//   // do various tests
//   std::array<double, 6> arr = {680, 5860, 14830, 1989, 1989, 1989};
//   if (test(6, 8000, arr))
//     passed++;
//     std::array<double, 6> arr2 = {1520, 13250, 0, 1768, 1768,0};
//   if (test(4, 9000, arr2))
//     passed++;
//   std::cout << "\nsum() passed " << passed << " tests.\n";
//   return passed;
// }

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
//   return passed ;
// }