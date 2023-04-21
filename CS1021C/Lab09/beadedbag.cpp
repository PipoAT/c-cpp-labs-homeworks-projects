#include <algorithm>
#include "beadedbag.h"
#include "item.h"
#include <vector>

// Implement the BeadedBag::size and BeadedBag::insert member functions here.

// Complete the implementation of the BeadedBag::contains member function.

/*
 * insert
 *
 * Checks the vector to see if the item is in the vector
 * and adds the item if false
 *
 * input: item
 * output: true/false
 */

void BeadedBag::insert(Item to_insert) {
	if (!(BeadedBag::contains(to_insert))) {
		bagcontents.push_back(to_insert);

	}
	
	
	
}
/*
 * size
 *
 * Returns the amount of items in the vector
 *
 * input: vector
 * output: integer size of vector
 */


int BeadedBag::size() {
	return bagcontents.size();

}

/*
 * contains
 *
 * Checks if an item is in the vector/list
 *
 * input: item
 * output: true/false
 */

bool BeadedBag::contains(Item maybe_contained_item) {
	int col;
	for (int i = 0; i < bagcontents.size(); ++i) {
		if (bagcontents[i].isEqual(maybe_contained_item)) {
			return true;
		}
	}
	return false;
} 


