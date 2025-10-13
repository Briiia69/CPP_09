#include "../include/utils.hpp"

bool check_date(const std::string line) {
  const int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  
  if ( line.length() != 11 || line[4] != '-' || line[7] != '-') return false;

  int year, month, day;

  year = std::atoi(line.substr(0, 4).c_str());
  month = std::atoi(line.substr(5, 7).c_str());
  day = std::atoi(line.substr(8, 10).c_str());

  if (year > 2025) return false;

  if (month < 1 || month > 12) return false;

  if (day < 1 || months[month - 1] < day) return false;

  return true;
}

bool check_value(float value) {
  if (value < 0) {
    std::cout << "Error: not a positive number." << std::endl;
    return false;
  } else if (value > 21000000) {
    std::cout << "Error: too large a number." << std::endl;
    return false;
  }
  return true;
}