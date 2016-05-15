#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>

#include <DatabaseHandler.h>
#include <ServerRequest.h>
#include <Logger.h>
#include <ServerFactory.h>
#include <ServerPointer.h>
#include <sshTester.h>

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

  string severName;

  Server *server;

  vector<unsigned int> VPNusers;
  time_t now;
  tm *ltm;

  string filename;
  string chap_secrets_filename;
  string inventory_filename;
  string VPNusername;
  string VPNpassword;

  ofstream chap_secrets;
  string iprange = "192.168.155.";
  unsigned int ipnumber = 210;

  ofstream inventory;

	string ansibleCommand;

  string logFile("/var/log/vpnporhours.log");
  string log("");

  ServerRequest request(argv[1]);

  ServerPointer *pointer =
      new ServerPointer(string("pointer.windmaker.net"), 8745);

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
        // Selecting the server's name
        severName = db->setServerName(token, zone);
        log = string("Server Name: ") + severName;
        writeLog(logFile, log);
        free(db);
        db = new DatabaseHandler(address, 3306, user, password, database);

        db->updateDBField(token, string("name"), string("string"), severName);
        db->updateDBField(token, string("name"), string("string"), severName);
        free(db);
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
        server = CreateServer(selectedProvider, token);
        server->setZone(zone);
        server->setServerName(severName);
        log = string("Server type: ") + server->serverType();
        writeLog(logFile, log);
        if (server->create()) {
          db->updateDBField(token, string("machine_id"), string("integer"),
                            server->getMachineID());
          db->updateDBField(token, string("ip"), string("string"),
                            server->getServerIP());
          db->updateDBField(token, string("true_zone"), string("string"),
                            server->getTrueZone());
          db->updateDBField(token, string("provider"), string("string"),
                            selectedProvider);
          db->updateDBField(token, string("status"), string("string"),
                            string("Setting up"));
          log = string("Server created");
          writeLog(logFile, log);
          log = string("True Server ID: ") + server->getMachineID();
          writeLog(logFile, log);
          log = string("IP: ") + server->getServerIP();
          writeLog(logFile, log);
          if (pointer->point(severName, server->getServerIP())) {
            cout << "POINTING SUCCESS" << endl;
          }

          // After poining we have to make our ansible variables
          now = time(0);
          ltm = localtime(&now);
          filename = string("serverName_") + to_string(1900 + ltm->tm_year) +
                     string("-");
          if (ltm->tm_mon < 10) {
            filename = filename + string("0");
          }
          filename = filename + to_string(ltm->tm_mon) + string("-");
          if (ltm->tm_mday < 10) {
            filename = filename + string("0");
          }
          filename = filename + to_string(ltm->tm_mday) + string("_");
          if (ltm->tm_hour < 10) {
            filename = filename + string("0");
          }
          filename = filename + to_string(ltm->tm_hour) + string(":");
          if (ltm->tm_min < 10) {
            filename = filename + string("0");
          }
          filename = filename + to_string(ltm->tm_min) + string(":");
          if (ltm->tm_sec < 10) {
            filename = filename + string("0");
          }
          filename = filename + to_string(ltm->tm_sec);
          chap_secrets_filename = string("/home/azas/Proyectos/vpnporhoras/ansible/files/secrets/") + filename;
          inventory_filename = string("/home/azas/Proyectos/vpnporhoras/ansible/inventories/") + filename;
					log = string("VPN USER PASSWORD FILE:") + chap_secrets_filename;
					writeLog(logFile,log);
					log	=string("VPN users:");
					writeLog(logFile,log);
					VPNusers	= db->getVPNUsers(token);
					if( VPNusers.size() )
					{
            chap_secrets.open(chap_secrets_filename.c_str());
            for (unsigned int userID : VPNusers) {
              db->getVPNUserPassword(userID, &VPNusername, &VPNpassword);
							writeLog(logFile,string("ID:") + to_string(userID));
							writeLog(logFile,string("user:")+VPNusername);
							writeLog(logFile,string("pass:")+VPNpassword);
							chap_secrets << VPNusername << "\t*\t" << VPNpassword << "\t*\t" << iprange << ipnumber << "\n";
							ipnumber++;
            }
            chap_secrets.close();
					}
					inventory.open(inventory_filename.c_str());
					inventory << "[target]\n" << server->getServerIP() <<"\n";
					inventory.close();
					writeLog(logFile,string("Waiting the server"));
					while(!testSSHConection(server->getServerIP(),22))
					{
						writeLog(logFile,string("Waiting...")); 
						usleep(1000000);
					}
					writeLog(logFile,string("Server Ready to deploy"));
					ansibleCommand = string("/usr/bin/ansible-playbook /home/azas/Proyectos/vpnporhoras/ansible/pptp_setup.yml -i ") + inventory_filename + string(" -e \"secrets_file=") + filename + string("\"");
					writeLog(logFile,ansibleCommand);
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
