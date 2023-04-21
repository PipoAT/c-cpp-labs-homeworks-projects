#include "Exception.h"
#include "OrderedList.h"
#include "Task2.h"
#include "Task3.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


int main()
{

	srand(time(NULL));
	OrderedList<int> o;
	TaskTwo<int> t;
	TaskThree<int> e;
	int* a, * b, * c;
	int randNum1, randNum2, randNum3, randNum4, randNum5, randNum6;
	int randomIndices[MAX_ITEMS];
	int add_count_ = 0, add_count_2 = 0, add_count_3 = 0;
	int remove_count_ = 0, remove_count_2 = 0, remove_count_3 = 0;
	int rand_val;
	int prgm_count = 0;


	for (int i = 0; i < MAX_ITEMS; i++) {
		randomIndices[i] = i;
	}
	for (int z = 0; z < 100; z++) {
		while (add_count_ < 30 || remove_count_ < 25) {
			rand_val = rand() % 2;
			if (rand_val == 0) {
				randNum1 = (rand() % 100);

				a = new int(randNum1);

				try {
					o.addItem(a);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					add_count_--;
				}
				add_count_++;
			}
			else {
				random_shuffle(&randomIndices[0], &randomIndices[MAX_ITEMS - 1]);

				randNum4 = randomIndices[0];


				try {
					o.removeItem(randNum4);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					remove_count_--;
				}


				remove_count_++;
			}
		}
		while (add_count_2 < 30 || remove_count_2 < 25) {
			rand_val = rand() % 2;
			if (rand_val == 0) {
				randNum2 = (rand() % 100);
				b = new int(randNum2);
				try {
					t.addItem(b);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					add_count_2--;
				}

				add_count_2++;
			}
			else {
				random_shuffle(&randomIndices[0], &randomIndices[MAX_ITEMS - 1]);

				randNum5 = randomIndices[0];


				try {
					t.removeItem(randNum5);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					remove_count_2--;
				}


				remove_count_2++;
			}
		}
		while (add_count_3 < 30 || remove_count_3 < 25) {
			rand_val = rand() % 2;
			if (rand_val == 0) {
				randNum3 = (rand() % 100);
				c = new int(randNum3);
				try {
					e.addItem(c);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					add_count_3--;
				}
				add_count_3++;
			}
			else {
				random_shuffle(&randomIndices[0], &randomIndices[MAX_ITEMS - 1]);

				randNum6 = randomIndices[0];


				try {
					e.removeItem(randNum6);
				}
				catch (Exception& ex) {
					cout << "EXCEPTION: " << ex.getMessage() << endl;
					cout << endl;
					remove_count_3--;
				}

				remove_count_3++;

			}
		}

		o.makeEmpty();
		t.makeEmpty();
		e.makeEmpty();
		add_count_ = 0;
		add_count_2 = 0;
		add_count_3 = 0;
		remove_count_ = 0;
		remove_count_2 = 0;
		remove_count_3 = 0;
	}
	cout << "100 runs count: (Array size " << MAX_ITEMS << ")" << endl;
	cout << "TASK ONE (Base Class): " << endl;
	o.display();
	cout << "TASK TWO (Derived Class 1): " << endl;
	t.display();
	cout << "TASK THREE (Derived Class 2): " << endl;
	e.display();


	return 0;
}