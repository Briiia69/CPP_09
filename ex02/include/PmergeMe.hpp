#pragma once

#include <deque>
#include <iostream>
#include <vector>

class PmergeMe
{
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

  std::vector<std::pair<int, int>> pair1();
  std::vector<std::pair<int, int>> pair2();

  void sort_pair(std::vector<std::pair<int, int>> &in);
  std::vector<int> extractBig(std::vector<std::pair<int, int>> &pair);
  std::vector<int> createMainStack(std::vector<int> &larger, std::vector<std::pair<int, int>> &pairs);
  std::vector<int> generateJacobsthal(int n);

private:
  int _straggler;
  std::vector<int> _stack_1;
  std::deque<int> _stack_2;
};
