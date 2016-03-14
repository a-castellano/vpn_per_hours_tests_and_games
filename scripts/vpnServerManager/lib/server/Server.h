// Server.h
// Álvaro Castellano Vela 11/03/2016

#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server
{
	public:
		Server( const std::string & );

		virtual bool create() = 0;
		virtual bool destroy() = 0;
		virtual bool powerOn() = 0;
		virtual bool powerOff() = 0;

		virtual const std::string serverType();
		const std::string getToken();
		~Server();

	private:
		std::string token;
		std::string state;
		unsigned int zone;
		std::string realZone;

};

#endif
