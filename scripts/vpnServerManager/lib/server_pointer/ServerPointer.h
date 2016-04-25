// ServerPointer.h
// Álvaro Castellano Vela - 25/04/2016

#include <string>
#include <iostream>

class ServerPointer
{
	public:
		ServerPointer(const unsigned int &);
		bool point(const std::string &, const std::string &);
		bool unpoint(const std::string &);
	private:
		unsigned int port;
};
