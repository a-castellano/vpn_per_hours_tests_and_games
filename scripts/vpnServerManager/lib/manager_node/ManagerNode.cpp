// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <stdio.h>
#include <boost/thread.hpp> 

void RequestsQueue::Enqueue(const std::string &request)
{
  boost::unique_lock<boost::mutex> lock( r_mutex );
  r_queue.push( request );
  r_cond.notify_one();
}

void RequestsQueue::Dequeue( std::string &data )
{
  boost::unique_lock<boost::mutex> lock( r_mutex );
  while ( r_queue.size() == 0 )
  {
    r_cond.wait(lock);
  }
  data = r_queue.front();
  r_queue.pop();
}

void requestManager(  )
{
  printf("Yo! I'm a thread.\n");
}

