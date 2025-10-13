#pragma once

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

#include "utils.hpp"

#define DATA_PATH "./data/data.csv"

class Exchange {
 public:
  // orthodox cannonical form
  Exchange();
  Exchange(const Exchange &src);
  Exchange &operator=(const Exchange &src);
  ~Exchange();

  // add Data/Input
  Exchange(std::string data_path);

  // function
  void complete(const std::string &file) const;

 private:
  std::map<std::string, float> _records;
};