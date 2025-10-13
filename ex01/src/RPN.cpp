#include "../include/RPN.hpp"

// orhtodox cannonical form

RPN::RPN() {}

RPN::RPN(const RPN &src) {
  if (this != &src) {
    _storage = src._storage;
  }
}

RPN &RPN::operator=(const RPN &src) {
  if (this != &src) {
    _storage = src._storage;
  }
  return *this;
}

RPN::~RPN() {}

// other constructor

RPN::RPN(const std::string &line) {
    std::istringstream iss(line);
    std::string token;

  while (iss >> token) {
  
    if (token.length() == 1 &&
        std::string("+-*/").find(token[0]) != std::string::npos) {
      if (_storage.size() < 2)
        throw std::runtime_error("Error: Not enough operands for operator");

      int right = _storage.top();
      _storage.pop();
      int left = _storage.top();
      _storage.pop();

      switch (token[0]) {
        case '+':
          _storage.push(left + right);
          break;

        case '-':
          _storage.push(left - right);
          break;

        case '*':
          _storage.push(left * right);
          break;

        case '/':
          if (right == 0) throw std::runtime_error("Error: Division by zero");
          _storage.push(left / right);
          break;
      }
      show(token[0]);
    } else {
      std::istringstream iss(token);
      int num;

      if (!(iss >> num) || !iss.eof()){
        std::cout << "error: " << token[0] << std::endl;
        throw std::runtime_error("Error: Invalid token");}
      else
        _storage.push(num);
      show(token[0]);
    }
  }

  if (_storage.size() != 1)
    throw std::runtime_error("Error: Invalid expression");

  std::cout << "RESULT: " << _storage.top() << std::endl;
}

void RPN::show(char c) const {
  std::stack<int> temp = _storage;
  std::cout << "DEBUG: " << c << std::endl;

  while (!temp.empty()) {
    std::cout << temp.top() << std::endl;
    temp.pop();
  }
}