// ServerFactory.h 13/03/2016
// Álvaro Castellano Vela

#ifndef SERVERFACTORY_H
#define SERVERFACTORY_H

#include <string>
#include "Server.h"

class ServerFactory {
public:
  ~ServerFactory() { m_FactoryMap.clear(); }

  static ServerFactory *Get() {
    static ServerFactory instance;
    return &instance;
  }

  void Register(const string &serverType, ServerFactory pfnCreate);
  Server *CreateServer(const string &animalName);

private:
  ServerFactory();
  ServerFactory(const ServerFactory &) {}
  ServerFactory &operator=(const ServerFactory &) { return *this; }

  typedef map FactoryMap;
  FactoryMap m_FactoryMap;
}

#endif
