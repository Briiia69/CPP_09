#include "../include/utils.hpp"

bool check_date(const std::string line) {
  const int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year, month, day;

  size_t ypos = line.find('-');
  if (ypos == std::string::npos) return false;
  size_t mpos = line.find('-', ypos);
  if (mpos == std::string::npos) return false;
  if (line.length() - mpos < 1) return false;
  if (!line[ypos + 1] || !line[mpos + 1]) return false;

  year = std::atoi(line.substr(0, ypos).c_str());
  month = std::atoi(line.substr(ypos + 1, mpos - ypos - 1).c_str());
  day = std::atoi(line.substr(mpos + 1).c_str());

  int maxDay = months[month - 1];

    if (month == 2) {
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeap) maxDay = 29;
  }

  if (month < 1 || month > 12) return false;
  if (day < 1 || maxDay < day) return false;
  if (year < 0) return false;

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