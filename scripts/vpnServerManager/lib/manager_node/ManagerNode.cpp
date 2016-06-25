// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <stdio.h>
#include <boost/thread.hpp> 
#include <boost/asio.hpp> 
#include <boost/log/trivial.hpp>

#include <unistd.h> //usleep

//VPN PROJECT LIBRARIES


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

void CurlLock::getLock()
{
  c_mutex.lock(); 
}

void CurlLock::releaseLock()
{
  c_mutex.unlock();
}

void LogLock::getLock()
{
  l_mutex.lock();
}

void LogLock::releaseLock()
{
  l_mutex.unlock();
}

std::string make_daytime_string() { 
  time_t now = time(0);
  return ctime(&now);
}

bool processRequests( const unsigned int &port,  const unsigned int &numthreads, RequestsQueue *requestsQueue, const std::string &logFolder, LogLock *logLock )
{
  using boost::asio::ip::tcp;

  std::string logFile = logFolder + std::string("Proccesser.log");
  std::string log("");
  log = std::string("Proccesser started!");

  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();

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
      
      logLock->getLock();
       writeLog(logFile, log);
      logLock->releaseLock();

 

      if( request == std::string( "__KILL_YOURSELF__" ) )
      {
         log = std::string("Sending killing to the managers."); 
         
  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();



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
    log = std::string("ERROR: ") + std::string(e.what());
    
     logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();

 

    return false;
  }
  log = std::string("Proccesser finished.");
  

  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();

  return true;
}

void requestManager( const unsigned int thread_id, RequestsQueue *requestsQueue, CurlLock * curlLock, const std::string &logFolder, LogLock *logLock )
{

  std::string request;

  std::string logFile = logFolder + std::string("Manager_") + std::to_string(thread_id) +std::string(".log");
  std::string log("");
  std::cout<<logFile<<std::endl;
  log = std::string( "Manager started." );

  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();



  

  for(;;) // I will be here forever
  {
    requestsQueue->Dequeue( request );
    log = std::string( "Request received -> " ) + request;
    

  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();



    if( request == std::string( "__KILL_YOURSELF__" ) )
    {
      log = std::string( "Kill message received... R.I.P." );
      
  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();



      break;
    }
    //The request hast to be processed
    usleep(5000000);
    curlLock->getLock();

    log = std::string( "Processing the curl requests" );
    
  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();


    
    usleep(10000000);

    log = std::string( "Curl request processed." );
    
  logLock->getLock();
  writeLog(logFile, log);
  logLock->releaseLock();



    curlLock->releaseLock();
    usleep(1000000);

    log = std::string( "Request totally processed." );
   
    logLock->getLock();  
    writeLog(logFile, log);
      logLock->releaseLock();


  }
}


