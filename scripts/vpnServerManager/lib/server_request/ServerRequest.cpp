// serverRequest.h
// Álvaro Castellano Vela 23/02/2016

#ifndef SERVERREQUEST_H
#include "ServerRequest.h"
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


ServerRequest::ServerRequest(std::string request)
{
	boost::split(processedRequest,request,boost::is_any_of("/"));
	correctRequest = false;
        if ( processedRequest.size() == 2 )
	{
		if ( processedRequest[0] == "create" || processedRequest[0] == "destroy" )
		{
			if ( processedRequest[1].size() == 60 )
			{
				correctRequest = true;
			}
		}

	}
}

bool ServerRequest::isCorrect()
{
	return correctRequest;	
}
