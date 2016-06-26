// VPNLog.cpp
// Álvaro Castellano Vela - 25/06/2016

#include "VPNLog.h"
#include <string>

#include <iostream>
#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <cstring>
#include <stdlib.h>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

void Logger::write(const std::string & filename, const std::string & message)
{
  logging::add_file_log(
      keywords::file_name = filename.c_str(),
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = "[%TimeStamp%]: %Message%"
      );
  logging::add_common_attributes();
  src::logger lg;
  logging::record rec = lg.open_record();
  if( rec )
  {
    logging::record_ostream strm(rec);
    strm << message;
    strm.flush();
    lg.push_record(boost::move(rec));
  }
}
