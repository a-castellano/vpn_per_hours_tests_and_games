// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#include "VPNLog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>

bool writeLog(  std::string logData )
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

  std::vector<std::string> elems;

  std::string delimiter = "__-*-__";

  size_t pos = 0;
  std::string processedlog(logData);
  std::string token;

  while ((pos = processedlog.find(delimiter)) != std::string::npos) {
    token = processedlog.substr(0,pos);
    elems.push_back(token);
    token.clear();
    processedlog.erase(0, pos + delimiter.length());
  }
  elems.push_back(processedlog);

  logFile = elems[0];
  data = elems [1];

  elems.clear();

  outfile.open( logFile.c_str() , std::ios_base::app );
  outfile << "[";
  outfile << str;
  outfile << "] - ";
  outfile << data;
  outfile << "\n";
  outfile.close();
  data.clear();
  logFile.clear();
  logData.clear();

  return true;
}
