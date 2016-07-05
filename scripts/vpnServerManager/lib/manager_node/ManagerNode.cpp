// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <boost/thread.hpp> 
#include <boost/asio.hpp> 

#include <unistd.h> //usleep

//VPN PROJECT LIBRARIES
#include <VPNLog.h>
#include <ServerRequest.h>
#include <DatabaseHandler.h>
#include <ServerFactory.h>


extern VPNQueue  requestsQueue;

// Functions

void VPNQueue::Enqueue(const std::string request)
{
  r_mutex.lock();
  r_queue.push(request);
  r_mutex.unlock();
}


void VPNQueue::Dequeue( std::string &data )
{
  r_mutex.lock();
  while ( r_queue.empty()  )
  {
    r_mutex.unlock();
    usleep(20000);
    r_mutex.lock();
  }
  data = r_queue.front();
  r_queue.pop();
  r_mutex.unlock();
}

bool VPNQueue::empty()
{
  bool is_empty;
  r_mutex.lock();
  is_empty = r_queue.empty();
  r_mutex.unlock();
  return is_empty;
}

void VPNLock::getLock()
{
  c_mutex.lock();
}

void VPNLock::releaseLock()
{
  c_mutex.unlock();
}

std::string make_daytime_string() {
  time_t now = time(0);
  return ctime(&now);
}

bool processRequests( const unsigned int &port,  const unsigned int &numthreads/*, VPNQueue *requestsQueue*/, VPNQueue * logQueue/*, const std::string &logFolder, LogLock *logLock*/ )
{
  using boost::asio::ip::tcp;

  std::string logFile("Proccesser.log__-*-__");
  std::string log;
  std::string kill_yoursefl("__KILL_YOURSELF__");
  log = std::string( logFile + "Proccesser started!");
  logQueue->Enqueue( log );
  log.clear();

  try
  {

    std::stringstream ss;
    std::string request;

    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), port);
    tcp::acceptor acceptor(io_service, endpoint);

    tcp::socket socket(io_service); 
    tcp::iostream stream;

    std::string message("ACK");

    boost::system::error_code ignored_error;

    for(;;)
    {

      //acceptor.accept(socket);
      
      acceptor.accept(*stream.rdbuf());
      
      ss << stream.rdbuf();
      request = std::string( ss.str() ) ;
      //stream << "ACK";
      boost::asio::write(socket, boost::asio::buffer(message), boost::asio::transfer_all(), ignored_error);
      stream.close();

      log = std::string( "Request received: " + request );
      logQueue->Enqueue(  logFile + log );
      log.clear();

      if( request == kill_yoursefl )
      {
         log = std::string("Sending killing to the managers.");
         logQueue->Enqueue( logFile + log );
         log.clear();

         for (unsigned int t=0 ; t < numthreads; t++) {
            requestsQueue.Enqueue( request );
         }
         break;
      }

      requestsQueue.Enqueue( request );
      ss.str("");
      request.clear();
      
      //log = std::string( "Request enqueued." );
      //logQueue->Enqueue(  logFile + std::string("__-*-__") + log );
      
      //free(stream);
    }

  }
  catch (std::exception &e) {

    std::cerr << e.what() << std::endl;
    //log = std::string("ERROR: ") + std::string(e.what());
    //logQueue->Enqueue( logFile + std::string("__-*-__") + log );

    return false;

  }

  log = std::string("Proccesser finished.");
  logQueue->Enqueue( logFile + log );
  log.clear();

  return true;
}

void requestManager( const unsigned int thread_id/*, VPNQueue *requestsQueue*/, VPNLock * curlLock, VPNQueue * logQueue, VPNLock * requestLock )
{

  std::string request;

  std::string command;
  std::string token;


  std::string address("paula.es.una.ninja");
  std::string user("vpn");
  std::string password("XLRc3H1y4Db0G4qR630Qk2xPF3D88P");
  std::string database("vpn");

  DatabaseHandler *db;
  DatabaseHandler *db_zones;
  unsigned int zone;
  std::vector<std::string> providers;
  std::string selectedProvider;
  unsigned int providerRandomId;

  std::string severName;

  Server *server;

  std::string logFile = std::string("Manager_") + std::to_string(thread_id) +std::string(".log")+ std::string("__-*-__") ;
  std::string log;

  log = std::string( "Manager ") + std::to_string( thread_id ) + std::string(" started." );
  logQueue->Enqueue( logFile + log );
  log.clear();

  for(;;) // I will be here forever
  {

    requestsQueue.Dequeue( request );

    log = logFile + request;
    logQueue->Enqueue( log );
    log.clear();


    if( request == std::string( "__KILL_YOURSELF__" ) )
    {
      log = std::string( "Kill message received... R.I.P." );
      logQueue->Enqueue( logFile  + log );

      break;

    }
/*
    ServerRequest *serverRequest = new ServerRequest( request );

    if ( serverRequest->isCorrect() ) {

      command = serverRequest->getCommand();
      token = serverRequest->getToken();

      log = std::string("Commad: ") + command;
      logQueue->Enqueue( logFile + std::string("__-*-__") + log );

      log = std::string("Token: ") + token;
      logQueue->Enqueue( logFile + std::string("__-*-__") + log );

      free( serverRequest );

      db = new DatabaseHandler(address, 3306, user, password, database);
    
      if (!db->dataIsWellFormed()) {
        log = std::string("Error: Database data is incorrect.");
        logQueue->Enqueue( logFile + std::string("__-*-__") + log );
        //Send some alert
      }
      else {
        zone = db->getServerZoneFromToken(token);
        if (db->hasError()) {
          log = std::string("Error: getServerZoneFromToken.");
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );
          free(db);
        }
        else {
          log = std::string("Zone: ") + std::to_string(zone);
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );
          severName = db->setServerName(token, zone);
          log = std::string("Server Name: ") + severName;
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );
          //free(db);

          //db = new DatabaseHandler(address, 3306, user, password, database);
          db->updateDBField(token, std::string("name"), std::string("string"), severName);
          db->updateDBField(token, std::string("name"), std::string("string"), severName);
          free(db);

          db_zones = new DatabaseHandler(address, 3306, user, password, std::string("vpn_zones"));
          providers = db_zones->getProvidersFromZone(zone);

          log = std::string("Providers: ");
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );

          for (std::string provider : providers) {
            logQueue->Enqueue( logFile + std::string("__-*-__") + provider );
          }

          if (providers.size() == 1) {
            selectedProvider = providers[0];
          }
          else {
            srand(time(NULL));
            providerRandomId = rand() % (providers.size());
            selectedProvider = providers[providerRandomId];
          }

          log = std::string("Selected provider: ") + selectedProvider;
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );

          free(db_zones);

          log = std::string("Creating server.");

          server = CreateServer(selectedProvider, token);
          server->setZone(zone);
          server->setServerName(severName);
          log = std::string("Server type: ") + server->serverType();
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );

          curlLock->getLock(); 

          //server->create();

          curlLock->releaseLock();
    
          log = std::string("Server created.");
          logQueue->Enqueue( logFile + std::string("__-*-__") + log );

          free(server);

        }
      }



    }// if ( serverRequest->isCorrect() ) 
    else{
      free(serverRequest);
      log = std::string("Server resquest incorrect.");
      logQueue->Enqueue( logFile + std::string("__-*-__") + log );
    }

*/
    usleep( (rand() % 10 + 1) * 100000 );
    log = logFile + std::string("Request totally processed.");
    logQueue->Enqueue( log );
    request.clear();
    log.clear();
  }//for
}

void logManager( const std::string &logFolder , std::vector<VPNQueue *> &logQueues )
{
    std::string data;
    std::string log;
    VPNQueue * logQueue;

    unsigned int killed_queues;
    unsigned int queue_size = logQueues.size();

    while( killed_queues != queue_size )//size = n trhead managers + one producer
    {
      for( unsigned int i = 0 ; i < logQueues.size() ; i++)
      {
        logQueue = logQueues[i];
        if( ! logQueue->empty() )
        {
          logQueue->Dequeue( data );
          if( data != std::string( "__KILL_YOURSELF__" ) )
          {
            log = logFolder + data ;
            writeLog( log );
            data.clear();
            log.clear();
          }
          else
          {
            killed_queues ++;
          }
        }
      }
      usleep(100000);

      //logQueue->Dequeue( data );

      //if( data != std::string( "__KILL_YOURSELF__" ) )
      //{
      //  writeLog( logFolder + data);
      //}
      //else
      //{
      //  break;
      //}
    }
}
