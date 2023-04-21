#include "date.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, Date d) {
  os << d.day << "-" << d.month << "-" << d.year;
  return os;
}
