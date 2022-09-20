#pragma once

#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include "net.h"


//class for users action
class User
{
public:
	//constructor
	User() {}
	User(const std::string& login, const std::string& passw, const std::string& name) :
		_login(login), _password(passw), _name(name) {}

	//destructor
	~User() {}

	//getters
	std::string getName() const;
	std::string getLogin() const;

	//setters
	void setName(const std::string& name);	
	
private:
	const std::string _login; //fixed to define user in chat
	std::string _password;
	std::string _name;
};
