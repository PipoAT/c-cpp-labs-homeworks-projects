#ifndef __BEADEDBAG_BEADEDBAG_HPP
#define __BEADEDBAG_BEADEDBAG_HPP

#include "item.h"
#include <vector>

class BeadedBag {
public:
  // Place your member function declarations here.
	
  // Here's the declaration for contains, to get you started:
	int size();
	void insert(Item to_insert);
	bool contains(Item maybe_contained_item);
	


private:

/*
 * bagcontents
 *
 * Creates vector
 */

	std::vector <Item> bagcontents;
};

#endif