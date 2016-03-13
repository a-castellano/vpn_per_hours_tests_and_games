#include <iostream>
#include <string>

#include <Log.h>

using namespace std;
using namespace dhlogging;

int main(int argc, char *argv[])
{
	if ( argc != 1 )
		return 1;

	string text ( argv[1] );
	Log logger("/var/log/prueba_c.log");

	logger.info_log(text);

	return 0;
}
