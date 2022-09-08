#pragma once

#include <map>
#include <filesystem>
#include "User.h"


//works with TCP server
class Chat
{
public:
	
	Chat() {}
	~Chat() {}

	//for net_client working
	

	//functions to work with a user information
	void addUser(Chat& cht, ClientTCP &client, const std::string& login, const std::string& name, const std::string& pass);
	void insertUser(const User& usr);
	void showUsers(ClientTCP &client);
	bool findUser(const std::string& login, ClientTCP &client);
	bool findUserByName(const std::string& name, ClientTCP &client);
	User* getUser(const std::string& login);
	User* getUserByName(const std::string& name);
	
	//reconstruct chat's state for a user
	void chatGetAllCollection(Chat& cht, User* usr, ClientTCP &client);
	void chatGetPersonalCollection(Chat& cht, User* usr, ClientTCP &client);

private:
	//vector for an active usr
	std::map <std::string, User> Users;
	
};
