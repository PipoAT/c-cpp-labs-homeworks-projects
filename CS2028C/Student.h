#pragma once
#include <string>
#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

//This whole file is a typical get and set class for a student. No fancythings here
class Student {
private:
	//Private variables for the student information
	string FirstName;
	string LastName;
	string MNumber;

public:
	Student(); //Constructor
	void SetFirst(string); //Gets the students First name
	void SetLast(string); //Gets the students Last name
	void SetMNum(string); //Gets the students M Number
	string GetFirst(); //Sends out the students First name to main function
	string GetLast(); //Sends out the students Last name to the main function
	string GetMNumber(); //Sends out the students M Number to the main function
};

Student::Student() {};

///////////These are called in the main function and have information passed to them //////////////////
///Sets private variables to the information being sent from the main function///
void Student::SetFirst(string first) {
	FirstName = first;
}

void Student::SetLast(string last) {
	LastName = last;
}

void Student::SetMNum(string Mnum) {
	MNumber = Mnum;
}

////////These are called in main function to sends information held in private memeber function to the main function///////
string Student::GetFirst()
{
	return FirstName;
}

string Student::GetLast() {
	return LastName;
}

string Student::GetMNumber()
{
	return MNumber;
}

#endif
