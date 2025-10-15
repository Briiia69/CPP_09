#include "../include/PmergeMe.hpp"

int main(int ac, char **av) {
  if (ac < 2) {
    std::cerr << "Error: No input sequence provided." << std::endl;
    return 1;
  }
  PmergeMe pmergeme;
  pmergeme.run<std::vector<int> >(ac, av);

  PmergeMe pmergeme1;
  pmergeme1.run<std::deque<int> >(ac, av);

  return 0;
}