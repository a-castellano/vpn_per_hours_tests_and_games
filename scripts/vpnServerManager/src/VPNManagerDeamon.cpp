// VPNManagerDeamon.cpp
// Álvaro Castellano Vela - 24/06/2016

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/thread.hpp>


#include <ManagerNode.h>

using boost::asio::ip::tcp;
using namespace std;
using namespace boost;

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

string make_daytime_string() {
  time_t now = time(0);
  return ctime(&now);
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

  std::stringstream ss;
  unsigned int portnumber = atoi( argv[1] );
  unsigned int numthreads = atoi( argv[2] );

  RequestsQueue *requestsQueue = new RequestsQueue();  

  boost::thread_group threads;

  for( int i = 0; i < numthreads ; i++ )
  {
    cout<<i<<endl;
    threads.add_thread( new boost::thread( requestManager, requestsQueue ) );
  }

  cout << "Port Number: " << portnumber << endl;
  cout << "Number of threads: " << numthreads << endl;

/*
ithis will become another thread
  try
  {
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), atoi(argv[1]));
    tcp::acceptor acceptor(io_service, endpoint);

    for(;;)
    {
      tcp::iostream stream;
      acceptor.accept(*stream.rdbuf());
      ss << stream.rdbuf() ;
      stream << "ACK" << make_daytime_string();
      requestsQueue.Enqueue( ss.str() )
      ss.str("");
    }

  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  */
  return 0;
}
