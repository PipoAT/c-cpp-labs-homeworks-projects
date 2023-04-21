
#include "mms.h"
#include <string>
#include <vector>

#include "mms.h"
#include <string>
#include <vector>
/*
 * int MMS::inventorySize()
 *
 * returns the size of adoptables
 *
 * input: none
 * output: adoptables.size()
 */
int MMS::inventorySize() {
	return adoptables.size();
}
/*
 * inventorySizeByShots
 *
 * returns an int of the pointer of hasshots (when true)
 *
 * input: boolean
 * output: integer
 */
int MMS::inventorySizeByShots(bool has_shots) const {
	int count{ 0 };
	for (auto& a : adoptables) {
		if (a->hasShot() == has_shots) {
			count += 1;
		}
	}
	return count;
}
/*
 * inventorySizeByType()
 *
 * returns int of the pointer and b->get type of the adpables string and if type == all;
 *
 * input: type
 * output: integer count
 *
 */
int MMS::inventorySizeByType(AdoptableType type)const {

	int count{ 0 };
	for (auto& b : adoptables) {
		if (b->getType() == type || type == ALL) {
			count += 1;
		}
	}
	return count;
}
/*
 * inventorySizeByRestrictions()
 *
 * check for if pointer and c->has restrictions is true and increase the count;
 *
 * input: boolean
 * output: counter integer
 *
 */
int MMS::inventorySizeByRestrictions(bool hasRestrictions) const {
	int count{ 0 };
	std::string var;
	for (auto& c : adoptables) {
		if (c->hasRestrictions(var) == hasRestrictions) {
			count += 1;
		}
	}
	return count;
}
/*
 * animalsInInventory()
 *
 * takes the pointer and gets the pointer
 * and gets first then last name with a space between
 *
 * input: none
 * output: returns a string of a vector
 *
 */
std::vector<std::string>MMS::animalsInInventory() const {

	std::vector<std::string> vec;
	for (auto& c : adoptables) {
		vec.push_back(c->getFirstName() + " " + c->getLastName());
	}
	return vec;
}
