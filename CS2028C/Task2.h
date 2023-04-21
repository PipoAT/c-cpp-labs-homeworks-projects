#pragma once
#include "OrderedList.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>


template <typename T>
class TaskTwo : public OrderedList<T> {
public:

	void addItem(T* obj) {
		int i = MAX_ITEMS - 1;
		while (this->items[i] != nullptr) {
			i--;
		}

		if (i < 0 || this->isFull()) {
			throw Exception("STACK OVERFLOW ERROR: exceeded number of max items");
		}
		this->items[i] = obj;
		this->opAdd++;
	}
};