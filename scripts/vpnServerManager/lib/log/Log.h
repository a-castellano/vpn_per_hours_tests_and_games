// Log.h
// Álvaro Castellano Vela 12/03/2016

#ifndef LOG_H
#define LOG_H

#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;

namespace dhlogging 
{
class Log
{
	public:
		static Logger* getInstance(std::string logFile = "default.log");
		void info_log( const std::string & );
	private:
		void init();
		src::severity_logger< severity_level > lg;
};
}
#endif
