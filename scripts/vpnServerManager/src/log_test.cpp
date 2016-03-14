#include <iostream>
#include <string>

#include <Log.h>

using namespace std;


int main(int argc, char *argv[])
{
	logging::add_common_attributes();  

	    using namespace logging::trivial;
	dhlogging::Logger::getInstance()->logInfo("himom");
	

	return 0;
}
