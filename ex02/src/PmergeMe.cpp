#include "../include/PmergeMe.hpp"

// orthodox cannonical form

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
  if (this != &src) {
    _stack_1 = src._stack_1;
    _stack_2 = src._stack_2;
  }
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
  if (this != &src) {
    _stack_1 = src._stack_1;
    _stack_2 = src._stack_2;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}

// helper
bool PmergeMe::isValidInt(const char *s) {
  if (!s || *s == '|0') {
    return false;
  }
  for (size_t i = 0; s[i]; i++) {
    if (!std::isdigit(s[i])) return false;
  }
  return true;
}

void PmergeMe::print(std::vector<int> stack) {
  std::vector<int>::iterator it = stack.begin();
  std::vector<int>::iterator ite = stack.end();

  while (it != ite) {
    std::cout << *it << std::endl;
    it++;
  }
}

void PmergeMe::print(std::deque<int> stack) {
  std::deque<int>::iterator it = stack.begin();
  std::deque<int>::iterator ite = stack.end();

  while (it != ite) {
    std::cout << *it << std::endl;
    it++;
  }
}

// create pair
std::vector<std::pair<int, int>> PmergeMe::pair1() {
  std::vector<std::pair<int, int>> res;
  std::vector<int>::iterator it = _stack_1.begin();
  std::vector<int>::iterator ite = _stack_1.end();

  while (it != ite) {
    int first = *it++;
    int second = (it != ite) ? *it++ : -1;

    if (second == -1) {
      _straggler = first;
      break;
    }
    res.push_back(std::make_pair(first, second));
  }
  return res;
}

std::vector<std::pair<int, int>> PmergeMe::pair2() {
  std::vector<std::pair<int, int>> res;
  std::deque<int>::iterator it = _stack_2.begin();
  std::deque<int>::iterator ite = _stack_2.end();

  while (it != ite) {
    int first = *it++;
    int second = (it != ite) ? *it++ : -1;

    if (second == -1) {
      _straggler = first;
      break;
    }

    if (first > second)
      res.push_back(std::make_pair(first, second));
    else
      res.push_back(std::make_pair(second, first));
  }
  return res;
}

// sort pair
void PmergeMe::sort_pair(std::vector<std::pair<int, int>> &in) {
  for (size_t i = 0; i < in.size(); i++) {
    for (size_t j = i + 1; j < in.size(); j++) {
      if (in[i].second > in[j].second) {
        std::pair<int, int> temp = in[i];
        in[i] = in[j];
        in[j] = temp;
      }
    }
  }
}

// extract big
std::vector<int> PmergeMe::extractBig(std::vector<std::pair<int, int>> &pair) {
  std::vector<int> larger;
  std::vector<std::pair<int, int>>::iterator it = pair.begin();
  std::vector<std::pair<int, int>>::iterator ite = pair.end();

  while (it != ite) {
    larger.push_back(it->second);
    it++;
  }

  return larger;
}



// function
void PmergeMe::run(int ac, char **av) {
  std::vector<int> initial_thing;
  for (size_t i = 1; i < ac; i++) {
    if (!isValidInt(av[i])) {
      std::cerr << "Error: Invalid input => \"" << av[i] << "\"" << std::endl;
      return;
    }
    initial_thing.push_back(std::atoi(av[i]));
  }

  // vector
  this->_stack_1 = initial_thing;
  print(this->_stack_1);
  std::vector<std::pair<int, int>> pairs1 = this->pair1();
  sort_pair(pairs1);

  // deque
  this->_stack_2.assign(initial_thing.begin(), initial_thing.end());
  print(this->_stack_2);
  std::vector<std::pair<int, int>> pairs2 = this->pair2();
  sort_pair(pairs2);

  // display results
  PmergeMe::print(this->_stack_1);
  PmergeMe::print(this->_stack_2);
}

// steps
//  pair by two
// sort pair min to max
// order pair by big from low to high
// extract big numbers and put them in a list
// add the first tiny number
// binary insertion
// display

// need to create the jacobstal suit
