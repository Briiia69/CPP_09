#include "../include/RPN.hpp"

int main(int ac, char **av) {
  // for (size_t i = 1; av[i]; i++) std::cout << av[i] << std::endl;
  if (ac < 2) {
    std::cerr << "Usage: " << av[0] << " <RPN expression>" << std::endl;
    return 1;
  }

  try {
    RPN rpn(av[1]);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
