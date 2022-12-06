#include "inputs.h"
#include <iostream>
#define PI 3.14159265
#include <algorithm>
#include <array>
#include <cmath>
#include <string.h>
#include <vector>

void active_filter_config();
std::array<double, 6> Butterworth(int poles, int fc);
std::array<double, 6> Chebyshev(int poles, int fc, std::string type,
                                int design);
void Select_Chebyshev(int db, std::string type, int stages,
                      std::vector<double> &b, std::vector<double> &a);
// bool test_sum(double a, double b, double expected); //unit test
// int run_sum_tests();
// bool test(double a, double b, std::array<double, 6> expected);
// int run_test();
// bool test_chebyshev(double a, double b, std::string c,
// std::array<double, 6> expected);

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

  if (design == 1) {
    // std::cout << "TEST1"
    // << "\n ";
    arr = Butterworth(poles, fc);
  }
  if (design == 2 || design == 3) {
    // std::cout << "TEST1"
    // << "\n ";
    arr = Chebyshev(poles, fc, type, design);
    std::cout << "\n " << arr[0] << "\n "; // testing outputs
    std::cout << "\n " << arr[1] << "\n "; // testing outputs
    std::cout << "\n " << arr[2] << "\n "; // testing outputs
    std::cout << "\n " << arr[3] << "\n "; // testing outputs
    std::cout << "\n " << arr[4] << "\n "; // testing outputs
    std::cout << "\n " << arr[5] << "\n "; // testing outputs
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
    // std::cout<< "\n "<< ra[i]<< "\n "; testing output    // cacluating for
    // all stages  and adding to array
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

// function to determine what array values to use
void Select_Chebyshev(int db, std::string type, int stages,
                      std::vector<double> &b, std::vector<double> &a) {
  // std::cout << "TEST";

  // array values for cn lp/hp and k for 0.5db
  // for both k first 3 are lp and last three are high pass

  double cnl1[3][3] = {{1.231, 0, 0}, {0.597, 1.031, 0}, {0.396, 0.768, 1.011}};
  // std::cout << "TEST1";
  double cnh1[3][3] = {{0.812, 0, 0}, {1.675, 0.970, 0}, {2.525, 1.302, 0.989}};
  double k1[3][3] = {{1.842, 0, 0}, {1.582, 2.660, 0}, {1.537, 2.448, 2.846}};
  // array values for cn lp/hp and k for 2db
  double cnl2[3][3] = {{0.907, 0, 0}, {0.471, 0.964, 0}, {0.316, 0.730, 0.983}};
  double cnh2[3][3] = {{1.103, 0, 0}, {2.123, 1.037, 0}, {3.165, 1.370, 1.017}};
  double k2[3][3] = {{2.114, 0, 0}, {1.924, 2.782, 0}, {1.891, 2.648, 2.904}};

  // if branches for 0.5/2 DB and if LP OR HP
  if (db == 2) {
    for (int i = 0; i < 3; i++) {
      // std::cout << "TEST2";
      b.push_back(k1[stages - 1][i]);
      if (type == "l") {
        a.push_back(cnl1[stages - 1][i]);
      }
      if (type == "h") {
        a.push_back(cnh1[stages - 1][i]);
      }
    }
  }
  // std::cout << "TEST2";
  if (db == 3) {
    for (int i = 0; i < 3; i++) {
      b.push_back(k2[stages - 1][i]);
      if (type == "l") {
        a.push_back(cnl2[stages - 1][i]);
      }
      if (type == "h") {
        a.push_back(cnh2[stages - 1][i]);
      }
    }
  }
}

// Fucntion to caluclate values for Chebyshev 0.5 or 2
std::array<double, 6> Chebyshev(int poles, int fc, std::string type,
                                int design) {
  // initialsing

  double rb = 10000;
  // std::cout << "TEST";
  double c = 0.00000001;
  std::array<double, 6> arr;
  std::vector<double> k;
  std::vector<double> array;
  int a = design;

  int stages = poles / 2;
  int i = 0;
  int z = 3;
  Select_Chebyshev(a, type, stages, k, array);
  // std::cout << "\n " << array[0] << "\n "; // testing outputs
  // std::cout << "\n " << array[1] << "\n "; // testing outputs
  // std::cout << "\n " << array[2] << "\n "; // testing outputs
  // std::cout << "\n " << k[0] << "\n ";     // testing outputs
  // std::cout << "\n " << k[1] << "\n ";     // testing outputs
  // std::cout << "\n " << k[2] << "\n ";     // testing outputs

  for (int e = 0; e < ((poles / 2)); e++) {
    // cacluating for all stages  and adding to

    if (array[e] == 0) {
      arr[i] = 0;
    } else {
      arr[i] = rb * (k[e] - 1);
      i = i + 1;
    }
    double f = fc;
    double cn = array[e];
    // cacluation with normalsing factor included
    double rc = (1 / (f * 2 * PI * cn));

    double r = rc / c;
    // std::cout << "\n " << r << "\n "; // testing outputs

    arr[z] = r;
    z = z + 1;
  }
  return (arr);
}
// Unit test code is from https://elec2645.github.io/106/testing.html

// // // Function to test combinations
// bool test_chebyshev(double a, double b, std::string c,
//                     std::array<double, 6> expected) {
//   std::array<double, 6> arr;
//   arr = Chebyshev(a, b, c);
//   int count = 0;
//   // for loop to check all values of the returned array
//   for (int i = 0; i < 6; i++) {
//     float s = round(arr[i]);
//     float s1 =round(expected[i]);

//     if (s1 == s) {
//       // count to ensure all values in array are correct
//       count = count + 1;

//     }
//   }

//   if (count == a) {
//     std::cout << "passed\n";
//     return true;
//   } else {
//     // print all expected values for comparison
//     for (int e = 0; e < 6; e++) {
//       std::cout << "FAILED! "
//                 << "\nGOT " << arr[e] << " (expecting " << expected[e]
//                 << ").\n";
//     }
//     return false;
//   }
// }

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

// function to run the tests
// int run_test() {
//   std::cout << "\nTesting sum()...\n" << std::endl;
//   // initialise counter for number of tests passed
//   int passed = 0;
//   // do various tests
//   std::array<double, 6> arr = {5370, 14480, 18460, 4019.06, 2072.33,
//   1574.23}; if (test_chebyshev(6, 10000, "l", arr))
//     passed++;
//   std::array<double, 6> arr2 = {5820, 16600, 0, 1055.75, 1823.08, 0};
//   if (test_chebyshev(4, 9000, "h", arr2))
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