#pragma once
#include "Exception.h"
#define MAX_ITEMS 30

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

template <typename T>
class OrderedList {
public:

	bool isFull() {
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (items[i] == nullptr) {
				return false;
			}
		}
		return true;
	}

	bool isEmpty() {
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (items[i] != nullptr) {
				return false;
			}
		}
		return true;
	}

	OrderedList() {
		opAdd = 0;
		opRemove = 0;
		items = new T * [MAX_ITEMS]();

	}

	void addItem(T* obj) {
		int i = 0;
		while (items[i] != nullptr) {
			i++;
		}

		if (i >= MAX_ITEMS || this->isFull()) {
			throw Exception("STACK OVERFLOW ERROR: exceeded number of max items");
		}
		items[i] = obj;
		opAdd++;
	}

	void removeItem(int index) {
		if (items[index] == nullptr || this->isEmpty()) {
			throw Exception("ERROR: Cannot remove empty values");
		}
		if (index == MAX_ITEMS - 1) {
			items[index] = nullptr;
			opRemove++;
		}
		else {
			for (int i = index; items[i] != nullptr; i++) {
				T* next = items[i + 1];
				items[i] = next;
				opRemove++;

			}
			items[MAX_ITEMS - 1] = nullptr;
		}
	}

	void makeEmpty() {
		for (int i = 0; i < MAX_ITEMS; i++) {
			items[i] = nullptr;
		}
	}

	void display() {
		cout << "Operations Performed by addItem method : " << opAdd << endl;
		cout << "Operations Performed by removeItem method : " << opRemove << endl;
		cout << "Operations Performed overall: " << opAdd + opRemove << endl;
	}
protected:
	T** items;
	int opAdd;
	int opRemove;

};
