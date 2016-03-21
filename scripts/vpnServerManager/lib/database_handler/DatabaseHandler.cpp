// DatabaseHandler.cpp
// Álvaro Castellano Vela 24/02/2016

#ifndef DATABASEHANDLER_H
#include "DatabaseHandler.h"
#endif

#ifndef STRING
#include <string>
#endif

#ifndef VECTOR
#include <vector>
#endif

#ifndef STDLIB
#include <stdlib.h>
#endif

#ifndef IOSTREAM
#include <iostream>
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
	error = false;
	errormsg = std::string("");

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
		this->driver = get_driver_instance();
		this->con = driver->connect(address, user, pass);
		this->con->setSchema(database);
		this->stmt = con->createStatement();
	} catch ( sql::SQLException &e ){
		connected = false;
		error = true;
		errormsg = std::string("Database conenction failed");
		return false;
	}
	error = false;
	connected = true;
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
	connect();
	if ( connected )
	{
		res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
	}
	this->disconnect();
}

const bool DatabaseHandler::hasError( void )
{
	return error;
}

std::string DatabaseHandler::getErrorMsg( void )
{
	return errormsg;
}

unsigned int  DatabaseHandler::getServerZoneFromToken( const std::string & token )
{
	std::stringstream query;
	query << "SELECT zone FROM servers WHERE token='" << token << "' LIMIT 1";
	connect();
	if ( connected )
	{
		this->res = stmt->executeQuery( query.str() );
		if (this->res->next())
		{
			//this->res->next();
			return std::stoi( this->res->getString("zone") );
		}
		else
		{
			disconnect();
			error = true;
			errormsg = std::string("Query response is empty.");
			return 0;
		}
	}
	else
	{
		std::cerr << "Failed to conenct" << std::endl;
		error = true;
		errormsg = std::string("Failed to conenct."); 
	}
	disconnect();
	return 0;
}

std::vector<std::string> DatabaseHandler::getProvidersFromZone( const unsigned int & zone_id )
{
	std::vector<std::string> providers;
	std::stringstream query;

	if ( database == "vpn_zones" )
	{
		connect();

		if ( connected )
		{
			query << "SELECT provider FROM zones WHERE zone_id=" << zone_id << " ;";
			res = stmt->executeQuery( query.str() );
			while ( res->next() )
			{
				providers.push_back( res->getString("provider") );
			}
		disconnect();  
		}
	
	}//providers will be emty
	return providers;
}
