// databaseHandler.cpp
// Álvaro Castellano Vela 24/02/2016

#ifndef DATABASEHANDLER_H
#include "databaseHandler.h"
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

databaseHandler::databaseHandler( std::string givenHost , unsigned int givenPort , std::string givenUser , std::string givenPass , std::string givenDatabase)
:host(givenHost), port(givenPort), user(givenUser), pass(givenPass), database(givenDatabase) 
{}
