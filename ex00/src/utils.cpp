#include "../include/utils.hpp"

bool check_date(const std::string line) {
  const int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year, month, day;

  size_t ypos = line.find('-');
  if (ypos == std::string::npos) return false;
  size_t mpos = line.find('-', ypos + 1);
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
  } else if (value > 1000) {
    std::cout << "Error: too large a number." << std::endl;
    return false;
  }
  return true;
}

std::string trim(const std::string &str) {
  size_t start = 0;
  size_t end = str.length();

  // Find first non-whitespace character
  while (start < end && (str[start] == ' ' || str[start] == '\t' ||
                         str[start] == '\n' || str[start] == '\r')) {
    start++;
  }

  // Find last non-whitespace character
  while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' ||
                         str[end - 1] == '\n' || str[end - 1] == '\r')) {
    end--;
  }

  return str.substr(start, end - start);
}

bool isValidNumber(const std::string &str) {
  if (str.empty()) return false;

  size_t i = 0;
  bool hasDot = false;

  // Skip leading whitespace (shouldn't be any after trim, but just in case)
  while (i < str.length() && str[i] == ' ') i++;

  // Check for optional sign
  if (i < str.length() && (str[i] == '+' || str[i] == '-')) {
    i++;
  }

  // Must have at least one digit
  bool hasDigit = false;

  // Check remaining characters
  while (i < str.length()) {
    if (str[i] >= '0' && str[i] <= '9') {
      hasDigit = true;
    } else if (str[i] == '.') {
      if (hasDot) return false;  // Second dot
      hasDot = true;
    } else if (str[i] == ' ') {
      // Trailing whitespace is ok, but nothing else should follow
      while (i < str.length()) {
        if (str[i] != ' ') return false;
        i++;
      }
      break;
    } else {
      return false;  // Invalid character
    }
    i++;
  }

  return hasDigit;
}