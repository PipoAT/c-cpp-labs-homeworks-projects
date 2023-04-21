#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;
class Student
{
private:

	string* FirstName = new string();
	string* LastName = new string();
	string* MNumber = new string();
	float* Birthday = new float;
	float* GPA = new float;

public:
	Student(string* First, string* Last, string* M, float* Birth, float* GPA =
		new float) {
		*FirstName = *First;
		*LastName = *Last;
		*MNumber = *M;
		*Birthday = *Birth;
		*(this->GPA) = *GPA;
	}
	string getName() {
		return (*FirstName + " " + *LastName);
	}
	string* GetMNumber() {
		return MNumber;
	}
	int GetAge() {
		int curryear = 2022;
		int year;
		cout << "Enter year of birth: ";
		cin >> year;
		int Age = curryear - year;
		return Age;
		
	
	}
	
	bool operator>(Student* other) {
		int a = atoi(((this->GetMNumber()))->substr(1).c_str());
		int b = atoi((*(other->GetMNumber())).substr(1).c_str());
		return a > b;
	}
	bool operator<(Student* other) {
		int a = atoi(((this->GetMNumber()))->substr(1).c_str());
		int b = atoi((*(other->GetMNumber())).substr(1).c_str());
		return a < b;
	}
	bool operator==(Student* other) {
		int a = atoi(((this->GetMNumber()))->substr(1).c_str());
		int b = atoi((*(other->GetMNumber())).substr(1).c_str());
		return a == b;
	}
	
	void Print() {
		cout << *GetMNumber() << " " << getName() << " " << GetAge() << endl;

	}
};

template <class DataType> struct node {
	DataType* data = 0;
	node* next = 0;
};

template <class DataType> class OrderedLL {
private:
	node<DataType>* _h = 0;
	int _s = 0;
	int _ind = 0;
public:
	OrderedLL() {
		node<DataType>* last = _h;
		while (last != 0 && _h != 0) {
			if (_h != 0) {
				last = _h;
				_h = _h->next;
			}
			if (last != 0) {
				delete last;
			}
		}
	}
	bool operator==(OrderedLL<DataType>* other) {
		if (this->Size() != other->Size()) {
			return false;
		}
		
		node<DataType>* loc1 = this->SeeAt(0), * loc2 = other->SeeAt(0);
		while (loc1 != 0) {
			if (loc1->data != loc2->data) {
				return false;
			}
			loc1 = loc1->next;
			loc2 = loc2->next;
		}
		return true;
	}
	bool operator<(OrderedLL<DataType>* other) {
		return this->Size() < other->Size();
	}
	bool operator>(OrderedLL<DataType>* other) {
		return this->Size() > other->Size();
	}

	void AddItem(DataType* data) {
		
		node<DataType>* nNode = new node<DataType>();
		
		(nNode->data) = (DataType*)(malloc(sizeof(DataType)));
		*(nNode->data) = *data;
		
		node<DataType>* loc = _h;
		node<DataType>* last = loc;
		while (loc != 0 && ((*(loc->data)) < ((nNode->data)))) {
			last = loc;
			loc = loc->next;
		}
			
			if (_h == 0) {
				_h = nNode;
			}
			else if (loc == _h) {
				nNode->next = loc;
				_h = nNode;
			}
			else {
				last->next = nNode;
				nNode->next = loc;
			}
		_s++;
	}
	DataType* GetItem(DataType* data) {
		node<DataType>* loc, * last;
		
		loc = _h;
		last = 0;
		while (loc != 0 && !(*(loc->data) == data)) {
			last = loc;
			loc = loc->next;
		}
		
		if (loc != 0) {
			if (last == 0) {
				_h = loc->next;
			}
			else if (loc->next == 0) {
				last->next = 0;
			}
			else {
				last->next = loc->next;
			}
		}
		_s--;
		
		if (loc == 0) {
			return 0;
		}
		return (loc->data);
	}
	bool IsEmpty() {
		return _h == 0;
	}
	bool IsInList(DataType* data) {
		node<DataType>* loc = _h;
		while (loc != 0) {
			if (*(loc->data) == data) {
				return true;
			}

			loc = loc->next;
		}
		return false;
	}
	int Size() {

			node<DataType> *loc = _h;
		int size = 0;
		while (loc != 0) {
			size++;
			loc = loc->next;
		}
		return size;
	}
	DataType* SeeNext() {
		if (IsEmpty()) {
			throw new range_error("Empty List Error");
		}
		if (_ind >= Size()) {
			return 0;
		}
		
		node<DataType>* loc = _h;
		for (int i = 0; i < _ind; i++) {
			loc = loc->next;
		}
		_ind++;
		return loc->data;
	}

	DataType* SeeAt(int* index) {
		
		if (*index > Size()) {
			throw new range_error("Index is outside of the size");
		}
		_ind = *index;
		return SeeNext();
	}
	void Reset() {
		_ind = 0;
	}

	void Print() {
		node<DataType>* loc = _h;
		while (loc != 0) {
			loc->data->Print();
			loc = loc->next;
		}
		cout << endl;
	}
};
void Menu()
{
	OrderedLL<Student>* myList = new OrderedLL<Student>();
	Student* TStudent;
	int* input = new int;
	int* input2 = new int;
	*input = -1;
	string* FirstName = new string(), * LastName = new string(), * Mnumber = new
		string(), * Birthday = new string();
	float* _year = new float, * _month = new float, * _day = new float;
	float* GPA = new float;
	string* sEntry = new string();
	bool _isInList;
	while (*input != 0) {
		cout << endl << endl;

			cout << " 0 - Exit" << endl
			<< " 1 - AddItem to list" << endl
			<< " 2 - GetItem from list" << endl
			<< " 3 - IsInList" << endl
			<< " 4 - IsEmpty " << endl
			<< " 5 - Size " << endl
			<< " 6 - SeeAt " << endl
			<< " 7 - SeeNext " << endl
			<< " 8 - Reset index " << endl
			<< " 9 - Clear list " << endl
			<< "10 - Print list " << endl
			<< " " << endl;
		cin >> *input;
		cout << endl << endl;
		switch (*input) {
			
		case 1:
			cout << "Inserting a new student into the list..." << endl;
			cout << "First Name: " << endl;
			cin >> *FirstName;
			cout << "Last Name: " << endl;
			cin >> *LastName;
			cout << "M Number: " << endl;
			cin >> *Mnumber;
			cout << "Birth year: " << endl;
			cin >> *_year;
			cout << "Do you wish to enter GPA? y/n" << endl;
			cin >> *sEntry;
			if (tolower(sEntry->c_str()[0]) == 'y') {
				cout << "GPA: " << endl;
				cin >> *GPA;
			}
			else {
				*GPA = 0;
			}
			myList->AddItem(new Student(FirstName, LastName, Mnumber, _day,
				GPA));
			break;
			
		case 2:
			cout << "What M# do you want to search for? : " << endl;
			cin >> *sEntry;
			TStudent = new Student(new string(""), new string(""), sEntry, new
				float);
			_isInList = myList->IsInList(TStudent);
			if (!_isInList) {
				cout << "That student is not on file." << endl;
			}
			else {
				TStudent = myList->GetItem(TStudent);
				TStudent->Print();
			}
			break;
		case 3:
			cout << "What M# do you want to search for? : " << endl;

				cin >> *sEntry;
			TStudent = new Student(new string(""), new string(""), sEntry, new
				float);
			_isInList = myList->IsInList(TStudent);
			if (_isInList) {
				cout << "That student is in the list." << endl;
			}
			else {
				cout << "That student is not in the list." << endl;
			}
			break;
		case 4:
			if (myList->IsEmpty()) {
				cout << "The List is empty. Please add to the list" << endl;
			}
			else {
				cout << "The List is not empty. " << myList->Size() << " items are in the list."<<endl;
			}
			break;
		case 5:
			cout << "The size of the list is " << myList->Size() << endl;
			break;
		case 6:
			cout << "Set Index. The size of the list is " << myList->Size() << " Index : "<<endl;
				cin >> *input2;
			TStudent = myList->SeeAt(input2);
			if (TStudent == 0) {
				cout << "There is no next item (at the end of the list)." <<
					endl;
			}
			else {
				TStudent->Print();
			}
			break;
		case 7:
			TStudent = myList->SeeNext();
			if (TStudent == 0) {
				cout << "There is no next item (at the end of the list)." <<
					endl;
			}
			else {
				TStudent->Print();
			}
			break;
			
		case 8:
			myList->Reset();
			cout << "The List idenx has been set to 0" << endl;
			break;
			
		case 9:
			delete myList;
			myList = new OrderedLL<Student>();
			cout << "The List has been deleted and reset" << endl;
			break;
			
		case 10:
			myList->Print();
			break;
		}
	}

}
int main() {
	Menu();
	return 0;
}