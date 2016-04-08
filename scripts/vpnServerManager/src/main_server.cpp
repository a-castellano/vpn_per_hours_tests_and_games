#include <iostream>
#include <string>
#include <vector>

#include <DatabaseHandler.h>
#include <ServerRequest.h>
#include <Logger.h>
#include <ServerFactory.h>

using namespace std;

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

  string logFile("/var/log/vpnporhours.log");
  string log("");

  ServerRequest request(argv[1]);

  log = string("Request: ") + string(argv[1]);
  writeLog(logFile, log);

  if (request.isCorrect()) {
    command = request.getCommand();
    token = request.getToken();
    log = string("Commad: ") + command;
    writeLog(logFile, log);
    log = string("Token: ") + token;
    writeLog(logFile, log);

    db = new DatabaseHandler(address, 3306, user, password, database);
    if (!db->dataIsWellFormed()) {
      log = string("Database data is incorrect.");
      writeLog(logFile, log);
      return -1;
    } else {
      zone = db->getServerZoneFromToken(token);
      if (db->hasError()) {
        writeLog(logFile, db->getErrorMsg());
        return -1;
      } else {
        log = string("Zone: ") + to_string(zone);
        writeLog(logFile, log);
        // Get providers
        db_zones = new DatabaseHandler(address, 3306, user, password,
                                       string("vpn_zones"));
        providers = db_zones->getProvidersFromZone(zone);
        log = string("Providers: ");
        writeLog(logFile, log);
        for (string provider : providers) {
          writeLog(logFile, provider);
        }
        // Get one provider randomply
        if (providers.size() == 1) {
          selectedProvider = providers[0];
        } else { // More than one provider
          srand(time(NULL));
          providerRandomId = rand() % (providers.size());
          selectedProvider = providers[providerRandomId];
        }
        log = string("Selected provider: ") + selectedProvider;
        writeLog(logFile, log);
        free(db_zones);
        free(db);
        server = CreateServer(selectedProvider, token);
        server->setZone(zone);
        log = string("Server type: ") + server->serverType();
        writeLog(logFile, log);
        // server->setMachineID(string("3622900"));
        if (server->create()) {
          log = string("Server created");
          writeLog(logFile, log);
          log = string("True Server ID: ") + server->getMachineID();
          writeLog(logFile, log);
          log = string("IP: ") + server->getServerIP();
          writeLog(logFile, log);
        }
        free(server);
      }
    }
  } else {
    log = string("Request malformed.");
    writeLog(logFile, log);
    return -1;
  }
	return 0;
}
