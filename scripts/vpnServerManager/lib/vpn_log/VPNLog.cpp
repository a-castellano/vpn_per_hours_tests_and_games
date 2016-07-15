// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#define BOOST_SP_USE_QUICK_ALLOCATOR
#include "VPNLog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <boost/shared_ptr.hpp>

bool writeLog(  boost::shared_ptr< std::string > path,  boost::shared_ptr< std::string > data)
{

  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

//  memoryLock->getLock();
//  boost::shared_ptr< std::string > logPath( path );
//  boost::shared_ptr< std::string > log( data );
//  memoryLock->releaseLock();

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y %H:%M:%S",timeinfo);
  std::string str(buffer);

  std::ofstream outfile;

  outfile.open( *path , std::ios_base::app );
  outfile << "[";
  outfile << str;
  outfile << "] - ";
  outfile << *data;
  outfile << "\n";

  outfile.close();

  str.clear();
  //logPath.reset();
  //log.reset();
  return true;
}
