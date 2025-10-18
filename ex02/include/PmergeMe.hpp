#pragma once

#include <deque>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <iomanip>
#include <limits>

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
  void print(T stack, T initial_thing) {
    {
      typename T::iterator it = initial_thing.begin();
      typename T::iterator ite = initial_thing.end();
      std::cout << "Before: ";
      while (it != ite) {
        std::cout << *it << " ";
        it++;
      }
      std::cout << std::endl;
    }

    {
      typename T::iterator it = stack.begin();
      typename T::iterator ite = stack.end();
      std::cout << "After: ";
      while (it != ite) {
        std::cout << *it << " ";
        it++;
      }
      std::cout << std::endl;
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
  void jacobsthalInsertion(T &small, T &larger) {
    if (small.size() == 0) return ;

    size_t n = small.size(); // size of the small contrainer
    std::vector<int> jacobs = generateJacobsthal(n);
    std::vector<bool> inserted(n, false); // vecotr checking if index is inserted
    int value = -1;

    // insert jacobs idexing
    for (size_t i = 0; i < n; i++) {
      size_t idx = jacobs[i] - 1;
      if (idx < n && !inserted[idx]) {
        // insert the num in the larger
        value = small[idx];
        typename T::iterator pos = std::lower_bound(larger.begin(), larger.end(), value);
        larger.insert(pos, small[idx]);
        inserted[i] = true;
      }
    }
    
    // insert none inserted numbers
    for (size_t i = 0; i < n; i++) {
      if (!inserted[i]) {
        value = small[i];
        typename T::iterator pos = std::lower_bound(larger.begin(), larger.end(), value);
        larger.insert(pos, small[i]);
        inserted[i] = true;
      }
    }
  }

  // perform fordJohnson algorithme
  template <typename T>
  void fordJohnson(T &stack) {

    int straggler = -1;
    std::vector<std::pair<int, int> > pairs = createPair(stack, straggler);
    
    sort_pair(pairs);

    T larger = extractBig<T>(pairs);
    T small = extractSmall<T>(pairs);

    if (larger.size() > 1) {
      T temp;
      temp.assign(larger.begin(), larger.end());
      fordJohnson(temp);
      stack.assign(temp.begin(), temp.end());
    }

    jacobsthalInsertion<T>(small, larger);

    if (straggler != -1) {
      typename T::iterator pos = std::lower_bound(larger.begin(), larger.end(), straggler);
      larger.insert(pos, straggler);
    }
   
    stack.assign(larger.begin(), larger.end());
  }

  // generate the jacobsthal suit for n
  std::vector<int> generateJacobsthal(size_t n);

  // initialise and launch algo
  template <typename T>
  void run(int ac, char **av, std::string type, bool list) {
    T initial_thing;

    for (size_t i = 1; i < static_cast<size_t>(ac); i++) {
      if (!isValidInt(av[i])) {
        std::cerr << "Error: Invalid input => \"" << av[i] << "\"" << std::endl;
        return;
      }

      // check int overflow underflow
      long num = std::atol(av[i]);
      if (num > std::numeric_limits<int>::max() || num < 0) {
        std::cerr << "Error: Invalid input => \"" << av[i] << "\"" << std::endl;
        return;
      }
      initial_thing.push_back(std::atol(av[i]));
    }

    // vector
    T stack;
    stack = initial_thing;
  
    clock_t start = clock();

    T mainStack;
    fordJohnson(stack);  // launch recursion

    clock_t end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // display results
    if (list == true) print<T>(stack, initial_thing);

    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << stack.size() << " element with " << type << " : " << time << " µs" << std::endl;
  }
};
