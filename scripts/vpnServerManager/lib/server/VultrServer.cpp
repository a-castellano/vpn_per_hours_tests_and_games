// VultrServer.cpp
// Álvaro Castellano Vela 12/03/2016

#define CURL_STATICLIB

#include "VultrServer.h"

#include <boost/asio.hpp>

using namespace boost::asio;

VultrServer::VultrServer(const std::string &token)
:Server(token)
{}

const std::string VultrServer::serverType( void )
{
        return std::string ("Vultr");
}

VultrServer::~VultrServer() {}

bool VultrServer::create()
{
	boost::system::error_code ec;
    io_service svc;
		    ip::tcp::socket sock(svc);
				    sock.connect({ {}, 8087 }); // http://localhost:8087 for testing
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
