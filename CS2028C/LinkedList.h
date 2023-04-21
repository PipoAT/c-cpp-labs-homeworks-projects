#pragma once
#include <cstdlib>
#include <iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>

class LinkedList
{
private:
   typedef struct node { //Creates a structure for pointer use
       T data; //Data type T will be known as data
       node* next; //will hold value of the next pointer in linked list
   } *nodePtr; //This is the name of the sturcture

   nodePtr head; //Holds data for the head of the linked list
   nodePtr curr; //Holds data for the current spot in the linked list
   nodePtr temp; //Holds data for the temporary spot in the linked list
   int counter = 0;

public:
   LinkedList();
   T item;
   void AddItem(T); //Adds Item
   void PrintList(); //Prints the list
   bool operator > (LinkedList<T>); //Comparison operators for array spots in main
   bool operator < (LinkedList<T>); //^^
   bool operator <= (LinkedList<T>); //^^
   bool operator == (LinkedList<T>); //^^
   ~LinkedList();
};


using namespace std;

template<class T>
LinkedList<T>::LinkedList() //Sets all the pointers to null
{
   head = NULL;
   curr = NULL;
   temp = NULL;
}

template<class T>
void LinkedList<T>::AddItem(T AddData) { //This is the mainly used function
   nodePtr n = new node; //Creates new node to store data
   n->next = NULL; //Sets next to null
   n->data = AddData; //Sets n data to data added in this case is a string

   if (head != NULL) { //This creates a new link if there is already something at the head of the chain
       curr = head; //The current is set to head
       while (curr->next != NULL) { //While both are not null
           curr = curr->next; //The next item in chain is set to next
       }
       curr->next = n; //The last item is set to n data
   }
   else {
       head = n; //If head is empty it equals n
   }
}


template<class T>
void LinkedList<T>::PrintList() { //Prints list
   curr = head; //The current equals the head
   while (curr != NULL) { //While current doesnt equal null
       cout << curr->data << endl; //Print the data of current
       curr = curr->next; //Get the next value in the chain
   }
};

//The operator functions used to compare values in the array
template<class T>
bool LinkedList<T>::operator > (LinkedList<T> input) //Head data is greater than input
{
   bool status;
   if (head->data > input.head->data) { //To convert the information into readable values and compare using operator
       status = true;
   }else {
       status = false;
   }

   return status;
}

template<class T>
bool LinkedList<T>::operator < (LinkedList<T> input) //Head data is less than input
{
   bool status;
   if (head->data < input.head->data) {
       status = true;
   }else {
       status = false;
   }

   return status;
}


template<class T>
bool LinkedList<T>::operator <= (LinkedList<T> input) //Head data is less than or equal to input
{
   bool status;
   if (head->data <= input.head->data) {
       status = true;
   }else {
       status = false;
   }

   return status;
}

template<class T>
bool LinkedList<T>::operator == (LinkedList<T> input) //Equal comparitor
{
   bool status;
   if (head->data == input.head->data) {
       status = true;
   }else {
       status = false;
   }

   return status;
}

template<class T> //Destructor
LinkedList<T>::~LinkedList()
{
}

#endif
