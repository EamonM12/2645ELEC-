#include <iostream>

void active_filter();

// errors
// incorectly called function actifiler
// notes
// converted input to evqivalent no for switch

int main() {
  std::string input;
  std::cout << "\n*******Filter Calculator*******\n";
  std::cout << "\nAre you designing a activer filer?(y/n)\n ";
  std::cin >> input;

  if (input == "y") {
    active_filter();
  } else if (input == "n") {

  } else {
    std::cout << "Inavlid input";
  }
}

void active_filter() {
  int i1, i2, i3;
  std::string input;
  std::cout << "\n High or low pass?:(h/l)\n ";
  std::cin >> input;

  if (input == "h") {
    i1 = 1;
  } else if (input == "l") {
    i1 = 2;
  } else {
    std::cout << "Inavlid input";
  }

  std::string input2;
  std::cout
      << "\n Buterrworth or Chebyshev(0.5Db)OR Chebyshev(2dB)?:(1/2/3)\n ";
  std::cin >> input2;
  i2 = stoi(input2);
  i3 = i1 + i2;

  // std::cout << i3; // Testing correct values for string

  switch (i3) {
  case 1:
    std::cout << "1"; // Testing all cases work
    break;
  case 2:
    std::cout << "2";
    break;
  case 3:
    std::cout << "3";
    break;
  case 4:
    std::cout << "4";
    break;
  case 5:
    std::cout << "5";
    break;
  case 6:
    std::cout << "6";
    break;
  }
}