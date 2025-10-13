#pragma once

#include <iostream>
#include <stack>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

class RPN {
 public:
  // orthodox cannonical form
  RPN();
  RPN(const RPN &src);
  RPN &operator=(const RPN &src);
  ~RPN();

  // other constructor
  RPN(const std::string &line);

  // debug
  void show(char c) const;

 private:
  std::stack<int> _storage;
};