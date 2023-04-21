#include "Exception.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Exception::Exception(const string& msg) {
	message = msg;
}

string Exception::getMessage() {
	return message;
}