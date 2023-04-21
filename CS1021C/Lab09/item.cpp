#include <string>
#include "item.h"

Item::Item(const std::string &item_name): m_name(item_name) {}

/*
 * getName
 *
 * Returns the name of a item
 *
 * output: name of item
 */

std::string Item::getName() {
  return m_name;
}

/*
 * isEqual
 *
 * Checks if the names of the items match
 *
 * input: name of item
 * output: true/false
 */


bool Item::isEqual(Item other_item) {
	if (other_item.getName() == m_name) {
		return true;
	}
	
		return false;
	
}