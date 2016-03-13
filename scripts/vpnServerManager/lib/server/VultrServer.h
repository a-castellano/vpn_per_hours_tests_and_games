// VultrServer.h
// Álvaro Castellano Vela 11/03/2016

#ifndef VULTRSERVER_H
#define VULTRSERVER_H

#include "Server.h"
#include <string>

class VultrServer : public Server {
public:
  VultrServer(const std::string &);

  bool create();
  bool destroy();
  bool powerOn();
  bool powerOff();

  const std::string serverType();

  ~VultrServer();

  static Server *__stdcall Create() { return new VultrServer(); }
};

#endif
