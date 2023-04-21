/*
Lab 05
Andrew Pipo, Sam Winkelmann, Huy Nguyen, Thavishka Gamage
*/


// Tasks 1 and 2 completed


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

using namespace std;


template<class T>
class Stack {
private:
    T* data;
    int size;
    int top;

    //Class Errors
    class Overflow {};
    class Underflow {};

public:
    Stack(int l) {
        size = l;
        data = new T[size];
        top = 0;
    }

    void push(T* input) {
        if (top >= size) {
            throw Overflow();
        }
        data[top] = *input;
        top += 1;
    }

    T* pop() {
        if (top < 0) {
            throw Underflow();
        }

        T* removedVal = &data[top];
        top--;
        return removedVal;
    }

    T* getTop() {
        return &data[top - 1];
    }

    int getVal() {
        return data[top - 1];
    }

    int getSize() {
        return top + 1;
    }

    void empty() {
        for (int i = 0; i < size; i++) {
            delete data[i];
        }
    }

    T* getData() {
        return data;
    }

    // Function for Printing purposes
    friend void printStack(Stack stack, int num) {
        cout << "Stack " << num << ": ";
        for (int i = stack.top - 1; i >= 0; i--) {
            cout << stack.data[i] << " ";
        }
        cout << endl;
    };
};

int main() {

    int disks;
    cout << "Enter the number of disks: ";
    cin >> disks;

    // Creates the three towers using stack
    Stack<int> row1(disks);
    Stack<int> row2(disks);
    Stack<int> row3(disks);
    Stack<int> endStack(disks);
    int input1;
    int input2;

    // Initialize for the first stack
    for (int i = 1; i <= disks; i++)
    {
        row1.push(&i);
        endStack.push(&i);
    }

    printStack(row1, 1);
    printStack(row2, 2);
    printStack(row3, 3);

    while (row3.getSize() != endStack.getSize()) {
        // Which stack to remove top disk from
        cout << "Pick a stack to remove a disk from the top: ";
        cin >> input1;
        if (input1 == 1) {
            // Which stack to put to disk on
            if (row1.getSize() == 1) {
                continue;
            }

            cout << "What stack would you like to move the top from stack " << input1 << " to: ";
            cin >> input2;
            while (input2 != 1 && input2 != 2 && input2 != 3) {
                cout << "Input is not valid, try again: ";
                cin >> input2;
            }
            if (input2 == 1) {
                cout << "You put the disk back into row 1\n";
            }
            
            else if (input2 == 2) {
                if (row2.getSize() == 1 || row1.getVal() > row2.getVal()) {
                    row2.push(row1.getTop());
                    row1.pop();
                }
                else {
                    cout << "Cannot move top of " << input1 << " into row 2!\n";
                }
            }
            
            else if (input2 == 3) {
                if (row3.getSize() == 1 || row1.getVal() > row3.getVal()) {
                    row3.push(row1.getTop());
                    row1.pop();
                }
                else {
                    cout << "Cannot move top of " << input1 << " into row 3!\n";
                }
            }
        }
        else if (input1 == 2) {
            if (row2.getSize() == 1) {
                continue;
            }

            // Which stack to put to disk on
            cout << "What stack would you like to move the top from stack " << input1 << " to: ";
            cin >> input2;
            while (input2 != 1 && input2 != 2 && input2 != 3) {
                cout << "Input is not valid, try again: ";
                cin >> input2;
            }
            
            if (input2 == 1) {
                if (row1.getSize() == 1 || row2.getVal() > row1.getVal()) {
                    row1.push(row2.getTop());
                    row2.pop();
                }
                else {
                    cout << "Cannot move top of row " << input1 << " into row 1!\n";
                }
            }
            else if (input2 == 2) {
                cout << "You put the disk back into row 2\n";
            }
            
            else if (input2 == 3) {
                if (row3.getSize() == 1 || row2.getVal() > row3.getVal()) {
                    row3.push(row2.getTop());
                    row2.pop();
                }
                else {
                    cout << "Cannot move top of " << input1 << " into row 3!\n";
                }
            }
        }
        else if (input1 == 3) {
            if (row3.getSize() == 1) {
                continue;
            }

            // Which stack to put to disk on
            cout << "What stack would you like to move the top from stack " << input1 << " to: ";
            cin >> input2;
            while (input2 != 1 && input2 != 2 && input2 != 3) {
                cout << "Input not valid, try again: ";
                cin >> input2;
            }
            
            if (input2 == 1) {
                if (row1.getSize() == 1 || row3.getVal() > row1.getVal()) {
                    row1.push(row3.getTop());
                    row3.pop();
                }
                else {
                    cout << "Cannot move top of " << input1 << " into row 1!\n";
                }
            }
            
            else if (input2 == 2) {
                if (row2.getSize() == 1 || row3.getVal() > row2.getVal()) {
                    row2.push(row3.getTop());
                    row3.pop();
                }
                else {
                    cout << "Cannot move top of " << input1 << " into row 2!\n";
                }
            }
            else if (input2 == 3) {
                cout << "You put the disk back into row 3\n";
            }
        }
        else {
            cout << "Input not valid, try again!\n";
        }

        printStack(row1, 1);
        printStack(row2, 2);
        printStack(row3, 3);
    }

    cout << "Game has ended!\n\n";

    return 0;
}

