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

  template <typename T>
  void print(T stack) {
    typename T::iterator it = stack.begin();
    typename T::iterator ite = stack.end();

    while (it != ite) {
      std::cout << *it << std::endl;
      it++;
    }
  }

  // create pairs of the given stack
  template <typename T>
  std::vector<std::pair<int, int> > createPair(T &stack, int &straggler) {
    std::vector<std::pair<int, int> > res;
    typename T::iterator it = stack.begin();
    typename T::iterator ite = stack.end();

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

  // extract big numbers in pair
  template <typename T>
  T extractBig(std::vector<std::pair<int, int> > &pair) {
    T larger;
    std::vector<std::pair<int, int> >::iterator it = pair.begin();
    std::vector<std::pair<int, int> >::iterator ite = pair.end();

    while (it != ite) {
      larger.push_back(it->second);
      it++;
    }

    return larger;
  }

  // extract small numbers in pair
  template <typename T>
  T extractSmall(std::vector<std::pair<int, int> > &pair) {
    T smallest;
    std::vector<std::pair<int, int> >::iterator it = pair.begin();
    std::vector<std::pair<int, int> >::iterator ite = pair.end();

    while (it != ite) {
      smallest.push_back(it->first);
      it++;
    }

    return smallest;
  }

  // binary insertion using jacobsthal suit
  template <typename T>
  void insertPending(T &mainStack, T &small, T &larger, int &straggler) {
    std::vector<int> jacobSthal =
        generateJacobsthal(small.size());  // temp value need to change it
  }

  // perform fordJohnson algorithme
  template <typename T>
  void fordJohnson(T &_stack, T &mainStack, T &small, T &larger) {

    std::vector<std::pair<int, int> > pairs;
    int straggler = -1;
    if (larger.size() == 0)
      pairs = createPair<T>(_stack, straggler);
    else
      pairs = createPair<T>(larger, straggler);

    sort_pair(pairs);

    larger = extractBig<T>(pairs);
    small = extractSmall<T>(pairs);

    if (larger.size() > 1) fordJohnson(_stack, mainStack, small, larger);

    if (larger.size() == 1) mainStack.push_back(*larger);

    insertPending(mainStack, small, larger, straggler);
  }

  // generate the jacobsthal suit for n
  std::vector<int> generateJacobsthal(int n);

  // initialise and launch algo
  template <typename T>
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
    T _stack;
    _stack = initial_thing;
    T larger, small;
    print<T>(_stack);

    T mainStack;
    fordJohnson(_stack, mainStack, larger, small);  // launch recursion

    // display results
    print<T>(_stack);
  }
};
