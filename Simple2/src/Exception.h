#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Exception {
	public:
	string message;
	Exception(string newMessage);
	friend ostream & operator << (ostream &out,const Exception &other);
};