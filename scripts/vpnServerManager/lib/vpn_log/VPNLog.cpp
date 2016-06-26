// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#include "VPNLog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>

void writeLog( const std::string &logData )
{
  using namespace boost;

  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y %H:%M:%S",timeinfo);
  std::string str(buffer);

  std::ofstream outfile;

  std::string logFile;
  std::string data;

  std::cout << logData << std::endl;

  typedef std::vector< std::string > split_vector_type;

  split_vector_type SplitVec;
  split_regex( SplitVec, logData, ("__-*-__"), token_compress_on );

  logFile = SplitVec[0];
  data = SplitVec[1];

  std::cout << logFile << std::endl;
  std::cout << data << std::endl;

  outfile.open( logFile.c_str() , std::ios_base::app );
  outfile << "[";
  outfile << str;
  outfile << "] - ";
  outfile << data;
  outfile << "\n";
  outfile.close();

}
