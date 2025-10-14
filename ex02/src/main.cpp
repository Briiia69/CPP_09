#include "../include/PmergeMe.hpp"

int main(int ac, char **av) {
  if (ac < 2) {
    std::cerr << "Error: No input sequence provided." << std::endl;
    return 1;
  }
  PmergeMe<std::vector<int> > pmergeme;
  pmergeme.run(ac, av);

  PmergeMe<std::deque<int> > pmergeme1;
  pmergeme1.run(ac, av);

  return 0;
}