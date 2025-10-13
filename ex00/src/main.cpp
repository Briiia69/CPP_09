#include "../include/Exchange.hpp"

int main(int ac, char **av) {
  if (ac == 2) {
    (void)av;
    Exchange bitecoin(DATA_PATH);
    try {
      bitecoin.complete(av[1]);
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  }
  return 0;
}