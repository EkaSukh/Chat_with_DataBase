//This is a Client version of the Chat
#include "Chat.h"



//add user in database via server connection
void Chat::addUser(Chat& cht, ClientTCP &client, const std::string& login, const std::string& name, const std::string& pass)
{
	//two positions is for operation descriptor
	// 11 is descriptor to findUser operation on server side
	client.clearBuffer();
	std::string descriptor = "11";
	int start = client.writeBuffer(0, descriptor);
	

	//copy login in buffer
	start = client.writeBuffer(start, login);
	
	//copy name in buffer
	start = client.writeBuffer(start, name);
	
	//copy name in buffer
	start = client.writeBuffer(start, pass);

	//client.showBuff();
	
	//connect and sedn data to the server
	client.clientConnect();
	client.writeOutput();  

	client.clientClose();

	
}

//add user in the inner container
void Chat::insertUser(const User& usr)
{
	Users.insert({ usr.getLogin(), usr});
}

//list availible users to write 
void Chat::showUsers(ClientTCP &client)
{
	client.clearBuffer();
	std::string descriptor = "13";
	int start = client.writeBuffer(0, descriptor);
	
	client.clientConnect();
	client.writeOutput(); 

	client.clearBuffer();
	client.readInput();
	client.clientClose();

	//client.showBuff(15);
	std::string list;
	client.readBuffer(0,list, '#');	

	std::cout << "The list of availible users to write to:\n";
	std::cout << list << "\n";
	
}

//find user login in database
bool Chat::findUser(const std::string& login, ClientTCP &client)
{
	//two positions is for operation descriptor
	// 10 is descriptor to findUser operation on server side
	client.clearBuffer();
	std::string descriptor = "10";
	int start = client.writeBuffer(0, descriptor);
	     
	start = client.writeBuffer(start, login);
    
    client.clientConnect();
    client.writeOutput();

	//client.showBuff(10);
    
	client.clearBuffer();
	client.readInput();
	
	int result = client.atBuff(0) - '0';
	client.clientClose();
    
	//std::cout << "result is " << result << "\n";
	if (result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}	
}

//find user name in database
bool Chat::findUserByName(const std::string& name, ClientTCP &client)
{
	//two positions is for operation descriptor
	// 12 is descriptor to findUserByName operation on server side
	client.clearBuffer();
	std::string descriptor = "12";
	int start = client.writeBuffer(0, descriptor);
	       

    start = client.writeBuffer(start, name);

	client.clientConnect();
    client.writeOutput();
    
	client.clearBuffer();
	client.readInput();
	
	int result = client.atBuff(0) - '0';
	client.clientClose();
    
	//std::cout << "result is " << result << "\n";
	if (result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}	

}

//return pointer on the user in the inner container via login
User* Chat::getUser(const std::string& login)
{
	std::map <std::string, User>::iterator usr = Users.find(login);
	
	if (usr != Users.end())
		return &(usr->second);
	else
		return nullptr;
}

//return pointer on the user in the inner container via name
User* Chat::getUserByName(const std::string& name)
{

	std::map <std::string, User>::iterator usr;
	for (usr = Users.begin();usr != Users.end();++usr)
	{
		std::string tmp = usr->second.getName();
		if (0 == tmp.compare(name))
			return &(usr->second);
	}	
	return nullptr;

}

//return list of availible messages from collection "for all"
void Chat::chatGetAllCollection(Chat& cht, User* usr, ClientTCP &client)
{   
	//construct a message to the server
	//descriptor for personal chat state information
	client.clearBuffer();

    std::string descriptor = "21";
	int start = client.writeBuffer(0, descriptor);

	start = client.writeBuffer(start, usr->getLogin());
	
	client.clientConnect();    
    client.writeOutput();

	client.clearBuffer();
	client.readInput();
	client.clientClose();

	//client.showBuff(30);

	std::string result;
	client.readBuffer(0, result, '#');
	std::cout << "Messages for all users:\n";
	std::cout << "Num.  Sender   Date     Time \n";
	std::cout << result << "\n";

}

//return list of availible messages from personal collection 
void Chat::chatGetPersonalCollection(Chat& cht, User* usr, ClientTCP &client)
{
	//construct a message to the server
	//descriptor for personal chat state information
	client.clearBuffer();

    std::string descriptor = "22";
	int start = client.writeBuffer(0, descriptor);

	start = client.writeBuffer(start, usr->getLogin());
	
	client.clientConnect();    
    client.writeOutput();

	client.clearBuffer();
	client.readInput();
	client.clientClose();

	//client.showBuff(30);

	std::string result;
	client.readBuffer(0, result, '#');
	std::cout << "Messages for you:\n";
	std::cout << "Num.  Sender   Date     Time \n";
	std::cout << result << "\n";

}
