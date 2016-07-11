// ManagerMode.h
// Álvaro Castellano Vela - 24/06/2016

#ifndef MANAGERNODE_H
#define MANAGERNODE_H
#endif

#include <string>
#include <queue>
#include <boost/thread.hpp>

class VPNLock
{
  public:
    void getLock();
    void releaseLock();

  private:
    boost::shared_mutex c_mutex;
};

class VPNQueue
{
  public:
    void Enqueue( std::string * );
    std::string * Dequeue( );
    bool empty();

  private:
    std::queue<std::string *>  r_queue; //The queue which stores requests
    boost::mutex r_mutex;
};



std::string make_daytime_string();

bool processRequests(const unsigned int , const unsigned int , VPNQueue *);
/* "processRequests" function opens one socket for receiving 
 * server requests from the distributor, when a request is received
 * it is validated and enqueued.
 *
 * If the received request is "__KILL_YOURSELF__" the manager will send the same message
 * to all the requestsManagers wich will commit suicide
*/
void requestManager( const unsigned int /*,VPNQueue **/, VPNLock *, VPNQueue *, VPNLock *);

void logManager( const std::string , std::vector< VPNQueue *> & );
