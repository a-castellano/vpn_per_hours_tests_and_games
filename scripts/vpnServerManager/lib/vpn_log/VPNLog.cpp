// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#include "VPNLog.h"
#include <string>

//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/utility/setup/file.hpp>
//#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/sources/severity_logger.hpp>
//#include <boost/log/sources/record_ostream.hpp>

//namespace logging = boost::log;
//namespace src = boost::log::sources;
//namespace sinks = boost::log::sinks;
//namespace keywords = boost::log::keywords;

#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

Logger::Logger( const std::string & filename)
:filename(filename){}

void Logger::write(const std::string & message)
{
  logging::add_file_log( filename.c_str() );
  logging::add_common_attributes();
  src::logger lg;
  logging::record rec = lg.open_record();
  if (rec)
  {
    logging::record_ostream strm(rec);
    strm << message;
    strm.flush();
    lg.push_record(boost::move(rec));
  }
}


/*
void Logger::init( )
{
  logging::add_file_log
  (
    keywords::file_name = filename.c_str(),
    keywords::rotation_size = 10 * 1024 * 1024,
    keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
    keywords::format = "[%TimeStamp%]: %Message%"
  );

  logging::core::get()->set_filter
  (
    logging::trivial::severity >= logging::trivial::info
  );

}

void Logger::write( const std::string &messge ){

  init();
  logging::add_common_attributes();

  using namespace logging::trivial;
  //src::severity_logger< severity_level > lg;

  BOOST_LOG_SEV(lg, info) << messge;
}
*/
