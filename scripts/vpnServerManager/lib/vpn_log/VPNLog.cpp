// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#include "VPNLog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

bool writeLog(  std::string * &logPath,  std::string * &log )
{

  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y %H:%M:%S",timeinfo);
  std::string str(buffer);

  std::ofstream outfile;

  outfile.open( *logPath , std::ios_base::app );
  outfile << "[";
  outfile << str;
  outfile << "] - ";
  outfile << *log;
  outfile << "\n";
  str.clear();
  free( logPath );
  free( log );
  return true;
}
