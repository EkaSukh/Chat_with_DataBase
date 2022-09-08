#include "User.h"


//геттеры
std::string User::getName() const { return _name; }
std::string User::getLogin() const { return _login; }

//сеттеры
void User::setName(const std::string& name) { _name = name; }
void User::setPass(const std::string& pass) { _password = pass; }
//проверка пароля
bool User::checkPass(const std::string& psw) { return (0 == psw.compare(_password)); }

