// ManagerMode.h
// Álvaro Castellano Vela - 24/06/2016

#ifndef MANAGERNODE_H
#define MANAGERNODE_H
#endif

#include <string>
#include <queue>
#include <boost/thread.hpp> 

class RequestsQueue
{
  public:
    void Enqueue( const std::string & );
    void Dequeue( std::string & );

  private:
    std::queue<std::string> r_queue; //The queue which stores requests
    boost::mutex r_mutex; 
    boost::condition_variable r_cond;
};

class CurlLock
{
  public:
    void getLock();
    void releaseLock();

  private:
    boost::mutex c_mutex;
};

class LogLock
{
  public:
    void getLock();
    void releaseLock();

  private:
    boost::mutex l_mutex;
};

std::string make_daytime_string();

bool processRequests(const unsigned int &, const unsigned int &, RequestsQueue *, const std::string &, LogLock *);
/* "processRequests" function opens one socket for receiving 
 * server requests from the distributor, when a request is received
 * it is validated and enqueued.
 *
 * If the received request is "__KILL_YOURSELF__" the manager will send the same message
 * to all the requestsManagers wich will commit suicide
*/
void requestManager( const unsigned int ,RequestsQueue *, CurlLock *, const std::string &, LogLock*);
