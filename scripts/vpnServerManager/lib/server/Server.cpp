// Server.cpp
// Álvaro Castellano Vela 11/03/2016

#include "Server.h"

Server::Server(const std::string &token)
:token(token)
{}

const std::string Server::getToken( void )
{
	return token;
}

const std::string Server::serverType( void )
{
        return std::string("None");
}

Server::~Server() {}

