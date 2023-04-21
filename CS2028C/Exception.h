#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
class Exception {
public:
	Exception(const string& msg);
	string getMessage();
private:
	string message;
};