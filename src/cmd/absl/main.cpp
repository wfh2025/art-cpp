#include <iostream>
#include "absl/strings/str_cat.h"

int main(int argc, char** argv)
{
  std::string name = "Alice";
  int age = 25;
  std::string result = absl::StrCat("Name: ", name, ", Age: ", age);
  std::cout << result << std::endl;
  return 0;
}