// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#ifndef VPNLOG_H
#define VPNLOG_H
#endif

#include <string>

/*
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;
*/
class Logger
{
  public:
    Logger( const std::string & );
    //void init();
    void write( const std::string & );

  private:
    std::string filename;
};
