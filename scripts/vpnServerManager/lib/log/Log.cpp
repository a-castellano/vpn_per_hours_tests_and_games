// Log.cpp
// Álvaro Castellano Vela

#include "Log.h"

namespace dhlogging 
{
void Log::init()
{
	logging::add_file_log
    	(
        	keywords::file_name = logfile,
        	keywords::rotation_size = 10 * 1024 * 1024,
		keywords::auto_flush = true ,
        	keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), 
        	keywords::format = "[%TimeStamp%]: %Message%"
    	);

	logging::core::get()->set_filter
	(
        	logging::trivial::severity >= logging::trivial::info
    	);
}

Log::Log( const std::string & logfile )
:logfile(logfile)
{
	init();	
	logging::add_common_attributes();
}

void Log::info_log( const std::string & text )
{
	BOOST_LOG_SEV(lg, info) << text;
}
}
