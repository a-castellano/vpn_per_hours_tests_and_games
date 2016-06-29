// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <stdio.h>
#include <boost/thread.hpp> 
#include <boost/asio.hpp> 

#include <unistd.h> //usleep

//VPN PROJECT LIBRARIES
#include <VPNLog.h>

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

void LogQueue::Enqueue(const std::string &loginfo)
{
  boost::unique_lock<boost::mutex> lock( l_mutex );
  l_queue.push( loginfo );
  l_cond.notify_one();
}

void LogQueue::Dequeue( std::string &data)
{
  boost::unique_lock<boost::mutex> lock( l_mutex );

  while ( l_queue.size() == 0 )
  {
    l_cond.wait(lock);
  }
  data = l_queue.front();
  l_queue.pop();

}


void CurlLock::getLock()
{
  c_mutex.lock();
}

void CurlLock::releaseLock()
{
  c_mutex.unlock();
}

std::string make_daytime_string() {
  time_t now = time(0);
  return ctime(&now);
}

bool processRequests( const unsigned int &port,  const unsigned int &numthreads, RequestsQueue *requestsQueue, LogQueue * logQueue/*, const std::string &logFolder, LogLock *logLock*/ )
{
  using boost::asio::ip::tcp;

  std::string logFile("Proccesser.log");
  std::string log("");
  log = std::string("Proccesser started!");
  logQueue->Enqueue( logFile + std::string("__-*-__") + log );

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

      log = std::string( "Request received: " ) + request;
      logQueue->Enqueue(  logFile + std::string("__-*-__") + log );

      if( request == std::string( "__KILL_YOURSELF__" ) )
      {
         log = std::string("Sending killing to the managers.");
         logQueue->Enqueue( logFile + std::string("__-*-__") + log );

         for (unsigned int t=0 ; t < numthreads; t++) {
            requestsQueue->Enqueue( request );
         }
         break;
      }

      requestsQueue->Enqueue( request );
      ss.str("");

      log = std::string( "Request enqueued." );
      logQueue->Enqueue(  logFile + std::string("__-*-__") + log );
    }

  }
  catch (std::exception &e) {

    std::cerr << e.what() << std::endl;
    log = std::string("ERROR: ") + std::string(e.what());
    logQueue->Enqueue( logFile + std::string("__-*-__") + log );

    return false;

  }

  log = std::string("Proccesser finished.");
  logQueue->Enqueue( logFile + std::string("__-*-__") + log );

  return true;
}

void requestManager( const unsigned int thread_id, RequestsQueue *requestsQueue, CurlLock * curlLock, LogQueue * logQueue )
{

  std::string request;

  std::string logFile = std::string("Manager_") + std::to_string(thread_id) +std::string(".log");
  std::string log("");

  log = std::string( "Manager ") + std::to_string( thread_id ) + std::string(" started." );
  logQueue->Enqueue( logFile + std::string("__-*-__") + log );

  for(;;) // I will be here forever
  {
    requestsQueue->Dequeue( request );
    log = std::string( "Request received -> " ) + request;

    logQueue->Enqueue( logFile + std::string("__-*-__") + log );


    if( request == std::string( "__KILL_YOURSELF__" ) )
    {
      log = std::string( "Kill message received... R.I.P." );
      logQueue->Enqueue( logFile + std::string("__-*-__") + log );

      break;

    }
    //The request hast to be processed
    usleep(5000000);
    curlLock->getLock();

    log = std::string( "Processing the curl requests" );
    logQueue->Enqueue( logFile + std::string("__-*-__") + log );

    usleep(10000000);

    curlLock->releaseLock();

    log = std::string( "Curl request processed." );
    logQueue->Enqueue( logFile + std::string("__-*-__") + log );

    usleep(1000000);

    log = std::string( "Request totally processed." );
    logQueue->Enqueue( logFile + std::string("__-*-__") + log );

  }
}

void logManager( const std::string &logFolder , LogQueue * logQueue )
{
    std::string logFile;
    std::string data;

    for(;;)
    {
      logQueue->Dequeue( data );

      if( data != std::string( "__KILL_YOURSELF__" ) )
      {
        writeLog( logFolder + data);
      }
      else
      {
        break;
      }
    }
}
