#include "../include/PmergeMe.hpp"

int main(int ac, char **av) {
  if (ac < 2) {
    std::cerr << "Error: No input sequence provided." << std::endl;
    return 1;
  }
  PmergeMe pmergeme;
  pmergeme.run(ac, av);
  return 0;
}