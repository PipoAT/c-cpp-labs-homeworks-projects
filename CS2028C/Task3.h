#pragma once
#include "OrderedList.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>


template <typename T>
class TaskThree : public OrderedList<T> {
public:


	void addItem(T* obj) {
		if (this->isFull()) {
			throw Exception("STACK OVERFLOW ERROR: exceeded number of max items");
		}
		int mid = ceil(MAX_ITEMS / 2.0) - 1;
		if (this->items[mid] == nullptr) {
			this->items[mid] = obj;
			this->opAdd++;
		}
		else {
			int arr[MAX_ITEMS * 2]; 
			for (int k = 0; k < MAX_ITEMS; k++) {
				arr[k] = k;
			}
			for (int l = MAX_ITEMS; l < (MAX_ITEMS * 2); l++) {
				arr[l] = l - MAX_ITEMS;
			}


			int i = mid;

			while (this->items[arr[i]] != nullptr) {
				MAX_ITEMS;
				i++;
				if (i >= ((2 * MAX_ITEMS) - 1)) {
					throw Exception("STACK OVERFLOW ERROR: exceeded number of max items");
					break;
				}
			}
			for (int j = i; j > mid; j--) {
				this->items[arr[j]] = this->items[arr[j - 1]];
				this->opAdd++;
			}
			this->items[mid] = obj;
			this->opAdd++;

		}


	}

	void removeItem(int index) {
		if (this->items[index] == nullptr || this->isEmpty()) {
			throw Exception("ERROR: Cannot remove empty values");
		}
		this->items[index] = nullptr;
		this->opRemove++;
	}
};

