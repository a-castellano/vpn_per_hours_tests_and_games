// DatabaseHandler.h
// Álvaro Castellano Vela 24/02/2016

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H
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

class DatabaseHandler
{

	public:
		DatabaseHandler( const std::string & , const unsigned int & , const std::string & , const std::string & , const std::string & );

		const bool dataIsWellFormed( void );
		bool connect( void );
		const bool successConected( void );
		bool disconnect( void );
		bool checkIfTokenExists( std::string );

	private:
		std::string address;
		std::string user;
		std::string pass;
		std::string database;
		bool dataWellFormed;
		bool connected;



                sql::Driver *driver;
                sql::Connection *con;
                sql::Statement *stmt;
                sql::ResultSet *res;

};
