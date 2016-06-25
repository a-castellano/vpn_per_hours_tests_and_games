// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <stdio.h>
#include <boost/thread.hpp> 
#include <boost/asio.hpp> 

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

std::string make_daytime_string() { 
  time_t now = time(0);
  return ctime(&now);
}

void requestManager( const unsigned int thread_id, RequestsQueue *requestsQueue )
{
  std::cout << "Yo! I'm the thread " << thread_id << std::endl;
  std::string request;

  for(;;) // I will be here forever
  {
    requestsQueue->Dequeue( request );
    std::cout << "Greetings from thread " << thread_id << ". I've received this request: " << request << std::endl;
    if( request == std::string( "__KILL_YOURSELF__" ) )
    {
      std::cout << "Trhead "<< thread_id << " ...Bye..." << std::endl;
      break;
    }
  }
}

bool processRequests( const unsigned int &port,  const unsigned int &numthreads, RequestsQueue *requestsQueue)
{
  using boost::asio::ip::tcp;
  try
  {

    std::stringstream ss;
    std::string request;

    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), port);
    tcp::acceptor acceptor(io_service, endpoint);

    for(;;)
    {
      tcp::iostream stream;
      acceptor.accept(*stream.rdbuf());
      ss << stream.rdbuf();
      request = ss.str();
      stream << "ACK" << make_daytime_string();

      if( request == std::string( "__KILL_YOURSELF__" ) )
      {
         for (unsigned int t=0 ; t < numthreads; t++) {
            requestsQueue->Enqueue( request );
         }
         break;
      }

      requestsQueue->Enqueue( request );
      ss.str("");
    }

  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}
