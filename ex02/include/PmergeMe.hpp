#pragma once

#include <deque>
#include <iostream>
#include <vector>

template <typename T>
class PmergeMe {
 public:
  // orthodox cannonical form
  PmergeMe();
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);
  ~PmergeMe();

  // helper
  bool isValidInt(const char *s);


  void print(T stack) {
    T::iterator it = stack.begin();
    T::iterator ite = stack.end();

    while (it != ite) {
      std::cout << *it << std::endl;
      it++;
    }
  }

  // function
  void run(int ac, char **av) {
    int straggler = -1;
    T initial_thing;

    for (size_t i = 1; i < static_cast<size_t>(ac); i++) {
      if (!isValidInt(av[i])) {
        std::cerr << "Error: Invalid input => \"" << av[i] << "\"" << std::endl;
        return;
      }
      initial_thing.push_back(std::atoi(av[i]));
    }

    // vector
    _stack = initial_thing;
    print<T>(_stack);

    std::vector<std::pair<int, int>> pairs = createPair<T>(_stack, straggler);
    sort_pair(pairs);

    std::vector<int> larger = extractBig(pairs);
    std::vector<int> mainStack = createMainStack(larger, pairs);

    // display results
    print<T>(_stack);
  }

  std::vector<std::pair<int, int> > createPair(T &stack, int &straggler) {
    std::vector<std::pair<int, int>> res;
    T::iterator it = stack.begin();
    T::iterator ite = stack.end();

    while (it != ite) {
      int first = *it++;
      int second = (it != ite) ? *it++ : -1;

      if (second == -1) {
        straggler = first;
        break;
      }
      res.push_back(std::make_pair(first, second));
    }
    return res;
  };

  void sort_pair(std::vector<std::pair<int, int> > &in);
  std::vector<int> extractBig(std::vector<std::pair<int, int> > &pair);
  std::vector<int> createMainStack(std::vector<int> &larger,
                                   std::vector<std::pair<int, int> > &pairs);
  std::vector<int> generateJacobsthal(int n);

 private:
  T _stack;
};
