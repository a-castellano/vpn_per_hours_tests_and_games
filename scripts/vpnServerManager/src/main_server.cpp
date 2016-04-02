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

int main(int argc, char *argv[]) {
  if (argc != 2)
    return -1;

  string command;
  string token;

  DatabaseHandler *db;
	DatabaseHandler *db_zones;
  unsigned int zone;
  vector<string> providers;
	string selectedProvider;
	unsigned int providerRandomId;

	Server *server;

  string log("");
  logging::add_common_attributes();

  ServerRequest request(argv[1]);

  log = string("Request: ") + string(argv[1]);
  dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);

  if (request.isCorrect()) {
    command = request.getCommand();
    token = request.getToken();
    log = string("Commad: ") + command;
    dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);
    log = string("Token: ") + token;
    dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);

    db = new DatabaseHandler(address, 3306, user, password, database);
    if (!db->dataIsWellFormed()) {
      dhlogging::Logger::getInstance("/var/log/vpnporhours.log")
          ->logInfo("Database data is incorrect.");
      return -1;
    } else {
      zone = db->getServerZoneFromToken(token);
      if (db->hasError()) {
        dhlogging::Logger::getInstance("/var/log/vpnporhours.log")
            ->logInfo(db->getErrorMsg());
        return -1;
      } else {
        log = string("Zone: ") + to_string(zone);
        dhlogging::Logger::getInstance("/var/log/vpnporhours.log")
            ->logInfo(log);
				// Get providers
				db_zones = new DatabaseHandler(address, 3306, user, password, string("vpn_zones"));
				providers = db_zones->getProvidersFromZone(zone);
				log = string("Providers: ");
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);
				for (string provider : providers)
				{
					dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(provider); 
				}
				//Get one provider randomply
				if (providers.size()==1){
					selectedProvider = providers[0];
				}
				else
				{//More than one provider
					srand(time(NULL));
					providerRandomId = rand()%(providers.size());
					selectedProvider = providers[providerRandomId];
				}
				log = string("Selected provider: ") + selectedProvider;
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);
				free(db_zones);
				free(db);
				server = CreateServer(selectedProvider,token);
				server->setZone(zone);
				log = string("Server type: ") + server->serverType();
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(log);
				if(server->create())
				{
				dhlogging::Logger::getInstance("/var/log/vpnporhours.log")->logInfo(string("Server Created")); 
				}
				free(server);
      }
    }
  } else {
    dhlogging::Logger::getInstance("/var/log/vpnporhours.log")
        ->logInfo("Request malformed.");
    return -1;
  }
  return 0;
}
