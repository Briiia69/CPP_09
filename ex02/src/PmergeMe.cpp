#include "../include/PmergeMe.hpp"

// orthodox cannonical form

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
  if (this != &src) {
    _stack = src._stack;
  }
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
  if (this != &src) {
    _stack = src._stack;
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

// create main stack
std::vector<int> PmergeMe::createMainStack(
    std::vector<int> &larger, std::vector<std::pair<int, int>> &pairs) {
  std::vector<int> mainStack;

  larger.push_back(pairs.begin()->first);
  for (size_t i = 0; i < larger.size(); i++) mainStack.push_back(larger[i]);

  return mainStack;
}

// merge insertion
std::vector<int> PmergeMe::generateJacobsthal(int n) {
  std::vector<int> res;

  if (n <= 0) return res;
  res.push_back(1);
  if (n == 1) return res;
  res.push_back(1);

  for (size_t i = 0; i < n; i++) {
    int num = res[i - 1] + 2 * res[i - 2];
    if (num > n) break;
    res.push_back(num);
  }

  return res;
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
