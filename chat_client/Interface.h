#pragma once

#include "Chat.h"


//interface to interract with the user
class Interface
{
public:
	
	Interface()
	{}
	~Interface() {}

	//first level of the interface
	bool Enable(Chat& chat, ClientTCP &client);

	//functions of the first level of the interface
	static void registration(Chat& cht, ClientTCP &client);
	void logIn(Chat& cht,  ClientTCP &client);
	void quit(Chat& cht);

	//second level of the interface
	bool startChat(Chat& cht, ClientTCP &client);

	//form the text of a message
	static void readTheInput(std::string& str);
	
private:
	//control interface level 
	bool enable = true;//firs level of the interface
	bool LoggedIn = false;//second level of the interface

	//user pointer to activate second level of the interface
	User* active_user = nullptr;
};

