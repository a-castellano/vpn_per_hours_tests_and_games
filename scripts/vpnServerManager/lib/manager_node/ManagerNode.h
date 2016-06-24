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

void processRequests(const unsigned int &);
void requestManager(  );
