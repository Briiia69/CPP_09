#include "../include/PmergeMe.hpp"

// orthodox cannonical form

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
  if (this != &src) {
    _stack_1 = src._stack_1;
    _stack_2 = src._stack_2;
  }
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
  if (this != &src) {
    _stack_1 = src._stack_1;
    _stack_2 = src._stack_2;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}

// helper
bool PmergeMe::isValidInt(const char *s) {
  if (!s || *s == '|0') {
    return false;
  }
  for (size_t i = 0; s[i]; i++) {
    if (!std::isdigit(s[i])) return false;
  }
  return true;
}

void PmergeMe::print(std::vector<int> stack) {
  std::vector<int>::iterator it = stack.begin();
  std::vector<int>::iterator ite = stack.end();

  while (it != ite) {
    std::cout << *it << std::endl;
    it++;
  }
}

void PmergeMe::print(std::deque<int> stack) {
  std::deque<int>::iterator it = stack.begin();
  std::deque<int>::iterator ite = stack.end();

  while (it != ite) {
    std::cout << *it << std::endl;
    it++;
  }
}

// function
void PmergeMe::run(int ac, char **av) {
  std::vector<int> initial_thing;
  for (size_t i = 0; i < ac; i++) {
    if (!isValidInt(av[i])) {
      std::cerr << "Error: Invalid input => \"" << av[i] << "\"" << std::endl;
      return;
    }
  }

  // before

  // vector
  this->_stack_1 = initial_thing;
  PmergeMe::print(this->_stack_1);

  // deque
  this->_stack_2 = initial_thing;
  PmergeMe::print(this->_stack_2);

  // after
  PmergeMe::print(this->_stack_1);
  PmergeMe::print(this->_stack_2);
}