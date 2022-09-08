//This is a server version of the Chat
#include "Interface.h"


int main()
{
	
	//Establish server and connect to database
	ServerTCP server;
	DataBase data;
	data.connectToDataBase();
	data.createDataBase();
	DBUsers dbUsers(&data, &server);
	DBMessAll dbMsgAll(&data, &server);
	DBMessPrs dbMsgPrs(&data, &server);

	Interface interface(&server, &dbUsers, &dbMsgAll, &dbMsgPrs);

	while (interface.Enable()) //server has onle one level of the interface
	{}
	
	return 0;
}
