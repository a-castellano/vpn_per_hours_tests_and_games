// VultrServer.cpp
// Álvaro Castellano Vela 12/03/2016

#include "VultrServer.h"

VultrServer::VultrServer( const std::string & token )
:Server(token) {}

const std::string VultrServer::serverType( void )
{
        return std::string ("Vultr");
}

VultrServer::~VultrServer() {}

bool VultrServer::create()
{
        return true;
}

bool VultrServer::destroy()
{
        return true;
}

bool VultrServer::powerOn()
{
        return true;
}

bool VultrServer::powerOff()
{
        return true;
}
