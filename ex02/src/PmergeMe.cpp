#include "../include/PmergeMe.hpp"

// orthodox cannonical form

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
  (void)src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) { 
  (void)src;
  return *this;
}

PmergeMe::~PmergeMe() {}

// helper 
bool PmergeMe::isValidInt(const char *s) {
  if (!s || *s == '\0') {
    return false;
  }
  for (size_t i = 0; s[i]; i++) {
    if (!std::isdigit(s[i])) return false;
  }
  return true;
}

// sort pair
void PmergeMe::sort_pair(std::vector<std::pair<int, int> > &in) {
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

// merge insertion
std::vector<int> PmergeMe::generateJacobsthal(size_t n) {
  std::vector<int> res;

  if (n <= 0) return res;
  res.push_back(1);
  if (n == 1) return res;
  res.push_back(1);

  for (size_t i = 2; i < n; i++) {
    size_t num = res[i - 1] + 2 * res[i - 2];
    if (num > n) break;
    res.push_back(num);
  }

  return res;
}

