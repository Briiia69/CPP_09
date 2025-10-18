#include "../include/Exchange.hpp"

// orthodox cannonical form
Exchange::Exchange() {}

Exchange::Exchange(const Exchange &src) { _records = src._records; }

Exchange &Exchange::operator=(const Exchange &src) {
  if (this != &src) {
    _records = src._records;
  }
  return *this;
}

Exchange::~Exchange() {}

// other constructor
Exchange::Exchange(std::string data_path) {
  std::ifstream fin;

  // open the data file
  fin.open(data_path.c_str());

  std::string date, s_value;

  // pass the first line
  std::getline(fin, date);

  // loop into the file
  while (std::getline(fin, date, ',') && std::getline(fin, s_value)) {
    _records.insert(
        std::pair<std::string, float>(date, std::atof(s_value.c_str())));
  }

  // close the data file
  fin.close();
}

// function
void Exchange::complete(const std::string &file) const {
  std::ifstream fin;
  std::string line, date, unit;
  std::map<std::string, float>::const_iterator it, ite;

  it = _records.begin();
  ite = _records.end();
  fin.open(file.c_str());

  if (!fin.is_open()) throw std::runtime_error("Error: could not open file.");

  std::getline(fin, line);

  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    std::getline(iss, date, '|');
    std::getline(iss, unit);

    // Trim whitespace from date and unit
    date = trim(date);
    unit = trim(unit);

    if (unit.empty()) {
      std::cout << "Error: bad input => " << date << std::endl;
    } else if (!check_date(date)) {
      std::cout << "Error: bad input => " << date << std::endl;
    } else if (!isValidNumber(unit)) {
      std::cout << "Error: bad input => " << date << std::endl;
    } else {
      // find the date or close enough
      std::map<std::string, float>::const_iterator record_value =
          _records.lower_bound(date);

      // go to lower ones only for non perfect match
      if (record_value == _records.end()) {  // if the date is out of bound
        if (!_records.empty())
          record_value--;  // got to the last one in db
        else {
          std::cout << "Error: no records available." << std::endl;
          continue;
        }
      } else if (record_value->first != date &&
                 record_value !=
                     _records.begin()) {  // if a "match" is found but not equal
                                          // we use the closest lowest
        --record_value;
      } else if (record_value->first != date &&
                 record_value ==
                     _records.begin()) {  // if it goes lower than our starting
                                          // date if it's a percfect match we
                                          // use it otherwise send error
        std::cout << "Error: no earlier record for date " << date << std::endl;
        continue;
      }

      // display
      float num = std::atof(unit.c_str());
      if (check_value(num)) {
        std::cout << record_value->first << " => " << num << " = "
                  << record_value->second * num << std::endl;
      }
    }
  }
  fin.close();
}