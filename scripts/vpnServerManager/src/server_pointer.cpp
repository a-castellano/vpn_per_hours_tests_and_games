// Álvaro Castellano Vela 
// 29/04/2016

#include <iostream>
#include <string>
#include <ServerPointer.h>

using namespace std;   

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return -1;
	}

	string subdomain(argv[1]);
	string ip(argv[2]);

	ServerPointer  *pointer = new ServerPointer(string("pointer.windmaker.net"),8745);

	if ( pointer->point(subdomain, ip) )
	{
		cout<< "SUCCESS" << endl;
	}
	else{
		cout << "FAILED" << endl;
	}

	delete pointer;

	return 0;
}
