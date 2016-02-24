// serverRequest.h
// Álvaro Castellano Vela 23/02/2016
#ifndef SERVERREQUEST_H
#define SERVERREQUEST_H
#endif

#ifndef STRING
#include <string>
#endif

#ifndef VECTOR
#include <vector>
#endif

#ifndef BOOST_ALGORITHM_STRING
#include <boost/algorithm/string.hpp>
#endif

class ServerRequest
{
        public:
                ServerRequest( std::string );
                bool isCorrect(void);

	private:
		std::vector<std::string> processedRequest;
		bool correctRequest;
};
