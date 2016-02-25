#include <iostream>
#include <DatabaseHandler.h>

using namespace std;

int main(int argc, char *argv[])
{
	cout << argc << endl;
        if ( argc != 5 )
                return 1;

	string address(argv[1]);
	string user(argv[2]);

	string password(argv[3]);
	string database(argv[4]);

	cout << user.length()  << endl;
	DatabaseHandler db(address,3306,user,password,database);
		
	if ( db.dataIsWellFormed() )
	{
		cout << "BIEN" << endl;
	}
	db.connect();
	if ( db.successConected() )
        {
                cout << "CONECTADO" << endl;
        }
	return EXIT_SUCCESS;
	
}
