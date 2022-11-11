#include "Exception.h"

	Exception::Exception(string newMessage) {
		message=newMessage;
	}
	// No use of Super Class because it is a friend function
	ostream & operator << (ostream &out,const Exception &other) {
		return out << other.message<<endl;
	}