#ifndef __UTILITIES_H
#define __UTILITIES_H

#include "mms.h"
#include <fstream>
#include <memory>
#include <string>
#include <algorithm>

std::string ltrim(std::string str) {
  if (str.length() && str.at(0) == ' ') {
    return str.erase(0, 1);
  }
  return str;
}

std::string rtrim(std::string str) {
  if (str.length() && str.at(str.length() - 1) == ' ') {
    return str.erase(str.length() - 1, 1);
  }
  return str;
}

std::string chomp(std::string str) { return ltrim(rtrim(str)); }

bool readNextAdoptable(std::ifstream &file,
                       std::unique_ptr<Adoptable> &adoptable) {
  char comma, dash;
  std::string first_name, last_name, type;
  char has_shots_raw{'n'};
  Date adoptable_since;
  double weight;
  bool has_shots{false};
  if (!(std::getline(file, first_name, ',') &&
        std::getline(file, last_name, ',') && std::getline(file, type, ',') &&
        (file >> adoptable_since.year) && (file >> dash) &&
        (file >> adoptable_since.month) && (file >> dash) &&
        (file >> adoptable_since.day) && (file >> comma) && (file >> weight) &&
        (file >> comma) && (file >> has_shots_raw))) {
    return false;
  }

  if (std::iscntrl(file.peek())) {
    file.seekg(1, std::ios_base::cur);
  }

  first_name = chomp(first_name);
  last_name = chomp(last_name);
  type = chomp(type);

  if (has_shots_raw == 'y') {
    has_shots = true;
  }

  if (type == "Turtle") {
    adoptable = std::make_unique<Turtle>(weight, has_shots, adoptable_since,
                                         first_name, last_name);
  } else if (type == "Dog") {
    adoptable = std::make_unique<Dog>(weight, has_shots, adoptable_since,
                                      first_name, last_name);
  } else if (type == "Cat") {
    adoptable = std::make_unique<Cat>(weight, has_shots, adoptable_since,
                                      first_name, last_name);
  } else {
    return false;
  }
  return true;
}

template <typename T>
bool contains(const T &needle, const std::vector<T> &haystack) {
  return std::any_of(haystack.begin(), haystack.end(), [&needle](const T &h) { return h == needle; });
}

#endif