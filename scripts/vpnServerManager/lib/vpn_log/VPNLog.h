// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#ifndef VPNLOG_H
#define VPNLOG_H
#endif

#include <string>
#include <boost/shared_ptr.hpp>

bool writeLog( boost::shared_ptr< std::string >, boost::shared_ptr< std::string > );
