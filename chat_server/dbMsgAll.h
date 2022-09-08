#pragma once

#include "dataBase.h"

//works with collection of messages for all users
class DBMessAll
{
    public:
    DBMessAll(DataBase* db, ServerTCP* ptr_server): dataBase(db), server(ptr_server) {std::cout << "Create a DBMsgAll object.\n";}
    ~DBMessAll(){} 
       
    //this functions only form SQL querry
    void addMessage(const std::string& login, const std::string& text);
    //this functions return values found with querry
    std::string packMsgInBuffer(int n, int start);
    std::string packAllMsgCOllectionInBuffer(int start);

    private:
    //this functions only form SQL querry    
    void getMessage(const int n);
    void composeAllMsgCOllection();

    DataBase* dataBase;
    MYSQL* mysql = dataBase->getDescriptorMYSQL();

    MYSQL_RES* res;
    MYSQL_ROW row;

    ServerTCP* server;
};