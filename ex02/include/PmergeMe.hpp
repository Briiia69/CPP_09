#pragma once

#include <deque>
#include <iostream>
#include <vector>

class PmergeMe {
 public:
  // orthodox cannonical form
  PmergeMe();
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);
  ~PmergeMe();

  // helper
  bool isValidInt(const char *s);
  void print(std::vector<int> stack);
  void print(std::deque<int> stack);

  // function
  void run(int ac, char **av);

 private:
  std::vector<int> _stack_1;
  std::deque<int> _stack_2;
};
