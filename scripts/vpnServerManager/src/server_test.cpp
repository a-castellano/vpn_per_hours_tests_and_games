#include <iostream>
#include <string>

#include <Server.h>
#include <DigitalOceanServer.h>
#include <VultrServer.h>

using namespace std;

int main(void) {
  string token("328482348239h42332h7326723hgh");

  Server *server = new DigitalOceanServer(token);
  Server *vserver = new VultrServer(token);

  cout << "hola" << endl;

  cout << server->getToken() << endl;
  cout << server->serverType() << endl;

	cout << "otro" << endl;

  cout << vserver->getToken() << endl;
  cout << vserver->serverType() << endl;
}
