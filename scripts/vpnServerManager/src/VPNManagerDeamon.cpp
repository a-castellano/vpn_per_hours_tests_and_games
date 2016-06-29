// VPNManagerDeamon.cpp
// Álvaro Castellano Vela - 24/06/2016

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

// Project libraries

#include <ManagerNode.h>

using namespace std;

// Global variables


// Support Functions

bool legal_int(char *str)
{
  while (*str != 0)
  {
    if( ! (isdigit(*str++)) )
    {
      return false;
    }
  }
  return true;
}

// Main function

int main( int argc, char *argv[] ) // port number and numthreads 
{

  if ( argc != 3)
  {
    return 1;
  }

  if ( ! legal_int( argv[1] ) || ! legal_int( argv[2] ) )
  {
    return 1;
  }

  boost::thread manager;
  boost::thread logger;

  std::stringstream ss;
  unsigned int portnumber = atoi( argv[1] );
  unsigned int numthreads = atoi( argv[2] );

  VPNQueue *requestsQueue = new VPNQueue();
  VPNQueue *logQueue = new VPNQueue();
  CurlLock * curlLock = new CurlLock();

  boost::thread_group threads;

  string logFolder= string("log/Manager_")+to_string(portnumber)+string("/");

  for( unsigned int i = 0; i < numthreads ; i++ )
  {
    threads.add_thread( new boost::thread( requestManager, i, requestsQueue, curlLock, logQueue ) );
  }

  manager = boost::thread( processRequests, portnumber, numthreads, requestsQueue, logQueue );

  logger = boost::thread( logManager, logFolder, logQueue ); 

  cout << "Port Number: " << portnumber << endl;
  cout << "Number of threads: " << numthreads << endl;

  manager.join();
  threads.join_all();

  logQueue->Enqueue("__KILL_YOURSELF__");

  logger.join();

  cout << "End" << endl;

  return 0;
}
