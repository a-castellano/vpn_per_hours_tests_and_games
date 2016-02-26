#include <iostream>
#include <DatabaseHandler.h>

using namespace std;

int main(int argc, char *argv[])
{
	cout << argc << endl;
        if ( argc != 6 )
                return 1;

	string address(argv[1]);
	string user(argv[2]);

	string password(argv[3]);
	string database(argv[4]);
	
	string token(argv[5]);

	unsigned int zone;

	cout << user.length()  << endl;
	DatabaseHandler db(address,3306,user,password,database);
		
	if ( db.dataIsWellFormed() )
	{
		cout << "BIEN" << endl;
	}
	zone = db.getServerZoneFromToken(token);
	
        
                cout << "ZONA -> "<< zone << endl;
        
	return EXIT_SUCCESS;
	
}
