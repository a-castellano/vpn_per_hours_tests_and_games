#include <iostream>
#include <string>
#include <vector>

#include <DatabaseHandler.h>
#include <ServerRequest.h>
#include <Log.h>
#include <ServerFactory.h>

using namespace std;
using namespace logging::trivial;

string address("paula.es.una.ninja");
string user("vpn");
string password("XLRc3H1y4Db0G4qR630Qk2xPF3D88P");
string database("vpn");

int main( int argc, char *argv[])
{
	if ( argc != 2 )
			return -1;

	string command;
	string token;

	DatabaseHandler *db;  
	unsigned int zone;
	vector<string> providers; 

	string log("");
	logging::add_common_attributes();


	ServerRequest request( argv[1] );

	
	log = string("Request: ") + string(argv[1]) ;
	dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);  
	
	if ( request.isCorrect() )
			 {
				command = request.getCommand();
				token = request.getToken();
				log = string("Commad: ") + command ;
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);   
				log = string("Token: ") + token;
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);

				db = new DatabaseHandler(address, 3306, user, password, database);
				cout << "DENTRO";
				if(! db->dataIsWellFormed() )
				{
					dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo("Database data is incorrect."); 
					return -1;
				}
				else
				{
					cout << "DENTRO";
					zone = db->getServerZoneFromToken(token);
					if (db->hasError())
					{
						dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo("Database Error.");
						return -1;
					}
					else{
						log = string("Zone: ") + to_string(zone);
						dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log); 
					}
				}
			 }
	else{
		dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo("Incorrect request!"); 
		return -1;
	}
	return 0;
}
