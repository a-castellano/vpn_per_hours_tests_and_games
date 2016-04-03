// VultrServer.cpp
// Álvaro Castellano Vela 12/03/2016

#define CURL_STATICLIB

#include "VultrServer.h"

#include <curl/curl.h>
#include <sstream>
#include <fstream>

#include <boost/property_tree/json_parser.hpp>

VultrServer::VultrServer(const std::string &token) : Server(token) {}

const std::string VultrServer::serverType(void) { return std::string("Vultr"); }

VultrServer::~VultrServer() {}

bool VultrServer::create() {

  std::stringstream header;
  std::ostringstream os;
  CURL *curl;
  CURLcode res;

	std::stringstream json_file; 
	std::stringstream json;

	boost::property_tree::ptree pt;

  curl = curl_easy_init();

  if (curl) {
    struct curl_slist *chunk = NULL;
    header << "API-Key: " << VULTR_API_KEY;
    chunk = curl_slist_append(chunk, header.str().c_str());
    chunk = curl_slist_append(chunk, "Host: api.vultr.com");
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://api.vultr.com/v1/account/info");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write);
    curl_easy_setopt(curl, CURLOPT_FILE, &os);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    }
    std::cout << os.str() << std::endl;
    curl_easy_cleanup(curl);
    curl_slist_free_all(chunk);

		json << os.str();
		/*
    json_file << std::string("/tmp/") << this->getToken().c_str() << std::string("_json_response");

		std::ofstream out(json_file.str().c_str());
		out << os.str();
		out.close();
*/
		boost::property_tree::read_json(json, pt);
		std::cout << pt.get_child("balance").get_value<std::string>() << std::endl;
  }
  return true;
}

bool VultrServer::destroy() { return true; }

bool VultrServer::powerOn() { return true; }

bool VultrServer::powerOff() { return true; }
