// ManagerMode.cpp
// Álvaro Castellano Vela - 24/06/2016

#include "ManagerNode.h"
#include <string>
#include <iostream>
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

void VPNQueue::Enqueue(std::string *request)
{
  r_mutex.lock();
  r_queue.push( request );
  r_mutex.unlock();
}


std::string * VPNQueue::Dequeue( )
{
  std::string * data;
  r_mutex.lock();
  while ( r_queue.empty()  )
  {
    r_mutex.unlock();
    usleep(2000);
    r_mutex.lock();
  }
  data = r_queue.front();
  r_queue.pop();
  r_mutex.unlock();
  return data;
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

bool processRequests( const unsigned int &port,  const unsigned int &numthreads, VPNQueue * logQueue )
{
  using boost::asio::ip::tcp;

  std::string *logFile;
  std::string *log;
  std::string noPointerLogFile("Proccesser.log");
  std::string kill_yourself("__KILL_YOURSELF__");

  log = new std::string("Proccesser started!");
  logFile = new std::string(noPointerLogFile);

  logQueue->Enqueue( logFile );
  logQueue->Enqueue( log );

  try
  {

    std::stringstream ss;
    std::string *request;

    std::string message("ACK");
    std::string received("Request received: ");

    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), port);
    tcp::acceptor acceptor(io_service, endpoint);

    tcp::socket socket(io_service);
    tcp::iostream stream;

    boost::system::error_code ignored_error;

    for(;;)
    {

      acceptor.accept(*stream.rdbuf());
      ss << stream.rdbuf();
      stream.flush();
      request = NULL;
      request = new std::string( ss.str() );
      boost::asio::write(socket, boost::asio::buffer(message), boost::asio::transfer_all(), ignored_error);
      stream.close();

      logFile = NULL;
      logFile = new std::string(noPointerLogFile);
      log = NULL;
      log = new std::string( received + *request );
      logQueue->Enqueue( logFile );
      logQueue->Enqueue( log );

      if( *request == kill_yourself )
      {
         logFile = NULL;
         logFile = new std::string(noPointerLogFile);
         log = NULL;
         log = new std::string("Sending killing to the managers.");
         logQueue->Enqueue( logFile );
         logQueue->Enqueue( log );

         delete(request);

         for (unsigned int t=0 ; t < numthreads; t++) {
            request = NULL;
            request = new std::string( kill_yourself );
            requestsQueue.Enqueue( request );
         }
         break;
      }
      else
      {
        requestsQueue.Enqueue( request );
      }
      ss.clear();
      //ss.str("");
      logFile = NULL;
      logFile = new std::string(noPointerLogFile);
      logQueue->Enqueue( logFile );
      log = NULL;
      log = new std::string("Request enqueued.");
      logQueue->Enqueue( log );
    }//for

  }
  catch (std::exception &e) {

    logFile = NULL;
    logFile = new std::string(noPointerLogFile);
    log = NULL;
    log = new std::string("ERROR: "  + std::string(e.what()));
    logQueue->Enqueue( logFile );
    logQueue->Enqueue( log );
    return false;

  }

  logFile = NULL;
  logFile = new std::string(noPointerLogFile);
  log = NULL;
  log = new std::string("Proccesser finished.");
  logQueue->Enqueue( logFile );
  logQueue->Enqueue( log );
  //log.clear();

  //The only time we enqueue one unique item
  
  logFile = NULL;
  logFile = new std::string( kill_yourself );
  logQueue->Enqueue( logFile );

  return true;
}

void requestManager( const unsigned int thread_id, VPNLock * curlLock, VPNQueue * logQueue, VPNLock * requestLock )
{

  std::string *request;

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
  std::string *kill_yourself = new std::string( "__KILL_YOURSELF__" );
  std::string processed("Request totally processed.");
  std::string received( "Request reveived -> " );
  std::string noPointerLogFile = std::string("Manager_") + std::to_string(thread_id) +std::string(".log");

  Server *server;

  std::string *logFile;
  std::string *log;

  logFile = NULL;
  logFile = new std::string(noPointerLogFile);
  log = NULL;
  log = new std::string( std::string( "Manager ") + std::to_string( thread_id ) + std::string(" started." ) );
  logQueue->Enqueue( logFile );
  logQueue->Enqueue( log );

  for(;;) // I will be here forever
  {

    request = requestsQueue.Dequeue( );
    
    logFile = NULL;
    logFile = new std::string(noPointerLogFile);
    log = NULL;
    log = new std::string( received + *request );
    logQueue->Enqueue( logFile );
    logQueue->Enqueue( log );


    if( *request == *kill_yourself )
    {
      logFile = NULL;
      logFile = new std::string(noPointerLogFile);
      log = NULL;
      log = new std::string( "Kill message received... R.I.P." );
      logQueue->Enqueue( logFile );
      logQueue->Enqueue( log );

      break;

    }

    //Process the request
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
    logFile = NULL;
    logFile = new std::string(noPointerLogFile);
    log = NULL;
    log = new std::string( processed );
    logQueue->Enqueue( logFile );
    logQueue->Enqueue( log );

    delete(request);

  }//for
}

void logManager( const std::string &logFolder , std::vector<VPNQueue *> &logQueues )
{
    std::string *logFile;
    std::string *logPath;
    std::string *log;
    std::string kill_yourself( "__KILL_YOURSELF__" );

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
          logFile = logQueue->Dequeue( );
          if( *logFile != kill_yourself )
          {
            logPath = NULL;
            logPath = new std::string( logFolder + *logFile );
            log = NULL;
            log = logQueue->Dequeue( );
            writeLog( logPath , log );
          }
          else
          {
            killed_queues ++;
          }
          delete(logFile);
        }
      }
      usleep(100000);

    }
}
