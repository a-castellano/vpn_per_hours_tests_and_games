// DatabaseHandler.cpp
// Álvaro Castellano Vela 24/02/2016

#ifndef DATABASEHANDLER_H
#include "DatabaseHandler.h"
#endif

#ifndef STRING
#include <string>
#endif

#ifndef MYSQL_CONNECTION_H
#include "mysql_connection.h"
#endif

#ifndef CPPCONN_DRIVER_H
#include <cppconn/driver.h>
#endif

#ifndef CPPCONN_EXCEPTION_H
#include <cppconn/exception.h>
#endif

#ifndef CPPCONN_RESULTSET_H
#include <cppconn/resultset.h>
#endif

#ifndef CPPCONN_STATEMENT_H
#include <cppconn/statement.h>
#endif

#ifndef CPPCONN_PREPARED_STATEMENT_H
#include <cppconn/prepared_statement.h>
#endif

#ifndef BOOST_REGEX
#include <boost/regex.hpp>
#endif

DatabaseHandler::DatabaseHandler( const std::string & givenHost , const unsigned int & givenPort , const std::string & givenUser , const std::string & givenPass , const std::string & givenDatabase)
:pass(givenPass), database(givenDatabase), connected(false) 
{
	// Check that the host and the port are valid
	boost::regex IPPattern("(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
	
	boost::regex URLPattern("([\\da-z\\.-]+)\\.([a-z\\.]{2,6})|(localhost)");

	std::stringstream ss;

	dataWellFormed = true;
	
	if( !( boost::regex_match (givenHost , IPPattern) || boost::regex_match (givenHost , URLPattern) ) || givenUser.length() > 17)
	// If givenHost isn't an IP address maybe it's a domain name
	{
		dataWellFormed = false;
	}
	else
	{
		ss << "tcp://" << givenHost << ":" << givenPort;
		address = ss.str();
		user = givenUser;
	}
	
}

const bool DatabaseHandler::dataIsWellFormed( void )
{
	return dataWellFormed;
}

const bool DatabaseHandler::successConected( void )
{
	if ( dataWellFormed )
	{
        	return connected;
	}
	else
	{
		return false;
	}
}

bool DatabaseHandler::connect( void )
{
	try {
		driver = get_driver_instance();
		con = driver->connect(address, user, pass);
		con->setSchema(database);
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
		
	} catch ( sql::SQLException &e ){
		connected = false;
		return false;
	}
	return true;
}

bool DatabaseHandler::disconnect( void )
{
	try {

		delete res;
                delete stmt;
                delete con;
		connected = false;

	} catch ( sql::SQLException &e ){
		return false;
	}
	return true;
}

bool DatabaseHandler::queryTest( void )
{
	this->connect();
	res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
	this->disconnect();
}

unsigned int  DatabaseHandler::getServerZoneFromToken( const std::string & token )
{
	std::stringstream query;
	query << "SELECT zone FROM servers WHERE token='" << token << "' LIMIT 1";
	this->connect();
	res = stmt->executeQuery( query.str() );
	res->next();
	return std::stoi( res->getString("zone") );
}
