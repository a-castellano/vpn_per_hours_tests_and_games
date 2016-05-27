#include <boost/asio.hpp>
#include <memory>
#include <iostream>

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

#include <thread>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;
using namespace std;

unsigned char * get_icon(int* pOutSize);
string address("paula.es.una.ninja");
string user("vpn");
string password("XLRc3H1y4Db0G4qR630Qk2xPF3D88P");
string database("vpn");

bool processRequest(std::string currentRequest) {
  std::string command;
  std::string token;

  DatabaseHandler *db;
  DatabaseHandler *db_zones;
  unsigned int zone;
  std::vector<std::string> providers;
  std::string selectedProvider;
  unsigned int providerRandomId;

  std::string severName;

  Server *server;

  std::vector<unsigned int> VPNusers;
  time_t now;
  tm *ltm;

  std::string filename;
  std::string chap_secrets_filename;
  std::string inventory_filename;
  std::string VPNusername;
	std::string VPNpassword;
  ofstream chap_secrets;
  string iprange = "192.168.155.";
  unsigned int ipnumber = 210;

  ofstream inventory;

  string ansibleCommand;

  string logFile("/var/log/vpnporhours.log");
  string log("");

  ServerRequest request(currentRequest);

  ServerPointer *pointer =
      new ServerPointer(string("pointer.windmaker.net"), 8745);

  log = string("Request: ") + currentRequest;
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
        free(db);
        return false;
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

        db_zones = new DatabaseHandler(address, 3306, user, password,
                                       string("vpn_zones"));
        providers = db_zones->getProvidersFromZone(zone);
        log = string("Providers: ");
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
					db->updateDBField(token, string("machine_id"), string("integer"), server->getMachineID());
					db->updateDBField(token, string("ip"), string("string"), server->getServerIP());
					db->updateDBField(token, string("true_zone"), string("string"), server->getTrueZone());
					db->updateDBField(token, string("provider"), string("string"), selectedProvider);
					db->updateDBField(token, string("status"), string("string"),string("Setting up"));
					log = string("Server created");
					writeLog(logFile, log);
          log = string("True Server ID: ") + server->getMachineID();
					writeLog(logFile, log);
					log = string("IP: ") + server->getServerIP();
					writeLog(logFile, log);
					if (pointer->point(severName, server->getServerIP())) {
						cout << "POINTING SUCCESS" << endl;
					}
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
					log = string("VPN users:");
					writeLog(logFile,log);
					VPNusers = db->getVPNUsers(token);
					if( VPNusers.size() ){
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
					usleep(50000000);
					writeLog(logFile,string("Server Ready to deploy"));
					ansibleCommand = string("/usr/bin/ansible-playbook /home/azas/Proyectos/vpnporhoras/ansible/pptp_setup.yml -i") + inventory_filename + string(" -e \"secrets_file=") + filename + string("\" --key-file=/home/azas/Proyectos/vpnporhoras/ssh_keys/id_rsa -e 'host_key_checking=False'");
					writeLog(logFile,ansibleCommand);
					std::system(ansibleCommand.c_str());

      }
			}//	if (server->create()) 
				free(server);

      return true;
    }
  } else {
    return false;
  }

  return true;
}

//###### End of processRequest

class session;

class http_headers
{
   std::string method;
   std::string url;
   std::string version;

   std::map<std::string, std::string> headers;

public:

   std::string get_response()
   {
      std::stringstream ssOut;
			std::string request;
			if (url.size() > 1){
			request = url.substr(1);
			}
			else
			{
				request = string("CHURRO");
			}
			std::cout << request << std::endl;

			std::thread t1(processRequest, request);
			t1.detach();
      if(true)
      {
         std::string sHTML = "<html><body><h1>H</h1></body></html>";
         ssOut << "HTTP/1.1 200 OK" << std::endl;
         ssOut << "content-type: text/html" << std::endl;
         ssOut << "content-length: " << sHTML.length() << std::endl;
         ssOut << std::endl;
         ssOut << sHTML;
      }
      else
      {
         std::string sHTML = "<html><body><h1>404 Not Found</h1><p>There's nothing here.</p></body></html>";
         ssOut << "HTTP/1.1 404 Not Found" << std::endl;
         ssOut << "content-type: text/html" << std::endl;
         ssOut << "content-length: " << sHTML.length() << std::endl;
         ssOut << std::endl;
         ssOut << sHTML;
      }
      return ssOut.str();
   }

   int content_length()
   {
      auto request = headers.find("content-length");
      if(request != headers.end())
      {
         std::stringstream ssLength(request->second);
         int content_length;
         ssLength >> content_length;
         return content_length;
      }
      return 0;
   }

   void on_read_header(std::string line)
   {
      //std::cout << "header: " << line << std::endl;

      std::stringstream ssHeader(line);
      std::string headerName;
      std::getline(ssHeader, headerName, ':');

      std::string value;
      std::getline(ssHeader, value);
      headers[headerName] = value;
   }

   void on_read_request_line(std::string line)
   {
      std::stringstream ssRequestLine(line);
      ssRequestLine >> method;
      ssRequestLine >> url;
      ssRequestLine >> version;

      std::cout << "request for resource: " << url << std::endl;
   }
};

class session
{
   asio::streambuf buff;
   http_headers headers;

   static void read_body(std::shared_ptr<session> pThis)
   {
      int nbuffer = 1000;
      std::shared_ptr<std::vector<char>> bufptr = std::make_shared<std::vector<char>>(nbuffer);
      asio::async_read(pThis->socket, boost::asio::buffer(*bufptr, nbuffer), [pThis](const error_code& e, std::size_t s)
      {
      });
   }

   static void read_next_line(std::shared_ptr<session> pThis)
   {
      asio::async_read_until(pThis->socket, pThis->buff, '\r', [pThis](const error_code& e, std::size_t s)
      {
         std::string line, ignore;
         std::istream stream {&pThis->buff};
         std::getline(stream, line, '\r');
         std::getline(stream, ignore, '\n');
         pThis->headers.on_read_header(line);

         if(line.length() == 0)
         {
            if(pThis->headers.content_length() == 0)
            {
               std::shared_ptr<std::string> str = std::make_shared<std::string>(pThis->headers.get_response());
               asio::async_write(pThis->socket, boost::asio::buffer(str->c_str(), str->length()), [pThis, str](const error_code& e, std::size_t s)
               {
                  std::cout << "done" << std::endl;
               });
            }
            else
            {
               pThis->read_body(pThis);
            }
         }
         else
         {
            pThis->read_next_line(pThis);
         }
      });
   }

   static void read_first_line(std::shared_ptr<session> pThis)
   {
      asio::async_read_until(pThis->socket, pThis->buff, '\r', [pThis](const error_code& e, std::size_t s)
      {
         std::string line, ignore;
         std::istream stream {&pThis->buff};
         std::getline(stream, line, '\r');
         std::getline(stream, ignore, '\n');
         pThis->headers.on_read_request_line(line);
         pThis->read_next_line(pThis);
      });
   }

public:

   ip::tcp::socket socket;

   session(io_service& io_service)
      :socket(io_service)
   {
   }

   static void interact(std::shared_ptr<session> pThis)
   {
      read_first_line(pThis);
   }
};

void accept_and_run(ip::tcp::acceptor& acceptor, io_service& io_service)
{
   std::shared_ptr<session> sesh = std::make_shared<session>(io_service);
   acceptor.async_accept(sesh->socket, [sesh, &acceptor, &io_service](const error_code& accept_error)
   {
      accept_and_run(acceptor, io_service);
      if(!accept_error)
      {
         session::interact(sesh);
      }
   });
}

int main(int argc, const char * argv[])
{
   io_service io_service;
   ip::tcp::endpoint endpoint{ip::tcp::v4(), 8080};
   ip::tcp::acceptor acceptor{io_service, endpoint};

   acceptor.listen();
   accept_and_run(acceptor, io_service);

   io_service.run();
   return 0;
}

