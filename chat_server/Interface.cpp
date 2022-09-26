#include "Interface.h"

/*
The porgram logic uses decriptors to define action requested from a client

  //these proceduers are for all client's states
10 "findUser"
11 "addUser"
12 "findUserByName"
13 "showUsers"

  //these procedures are for logged in user only
20 "logIn"
21 "reconstruction of the common user's collection"
22 "reconstruction of the personal user's collection"
23 "send message to all other users"
24 "send message to a defined user"
25 "read message from "for all" collection
26 "read message from a personal user's collection"
27 "enter personal mode to change name or password"
*/

//first level of the interface
bool Interface::Enable()
{
	
		
	std::cout << "Waiting for message from a client...\n";

	//read a descriptor from a client's message	
	int input = server->readInput();
	
	//move through the menu
		switch (input)
		{
			
			case 10:
			{//finding user by login
				
				std::cout << "Doing \"findUser\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				server->readBuffer(0, login);
        		
				//check if a user exists
				std::cout <<"login is \"" << login << "\"\n";
				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"Find User\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				//bool find = chat.findUser(login);
				bool find = baseUsers->findUserByLogin(login);
				std::cout << "result of finding is " << find << "\n";
				
				//compose an answer
				server->clearBuffer();
				if(find)
					{
						std::string result = "1";
						server->writeBuffer(0, result);
					}
				else
					{
						std::string result = "0";
						server->writeBuffer(0, result);						
					}
				
				server->writeOutput();	

				return enable;
			
			}
			//This is an action to put new user in the chat
			case 11:
			{//add user operation
				
				std::cout << "Doing \"addUser\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				int n = server->readBuffer(0, login);								
				std::cout <<"login reconstruction: \"" << login << "\"\n";
				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"add a new User\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}
				
				//Read a user's name that is in the buffer
				std::string name;
				n = server->readBuffer(n, name);
				std::cout <<"name reconstruction: \"" << name << "\"\n";
				
				//Read a user's pass that is in the buffer
				std::string pass;
				server->readBuffer(n, pass);
				std::cout <<"pass reconstruction: \"" << pass << "\"\n";
				
				//construct an object  and put a user in the list of users				
				baseUsers->insertUserInTable(login, name, pass);
				std::cout << "Your user account successfully created.\n";

				return enable;			
			}

			case 12:
			{//find user by name
				std::cout << "Doing \"findUserByName\" operation\n";							
				
				//Read a user's login that is in the buffer				
				std::string name;
				server->readBuffer(0, name);				
				std::cout <<"name is \"" << name << "\"\n";
				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"find a User by name\" operation for \"" + name + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				//check if a user exists
				
				bool find = baseUsers->fingUserByName(name);
				std::cout << "result of finding is " << find << "\n";
				
				//compose an answer
				if(find)
					{
						std::string result = "1";
						server->writeBuffer(0, result);
					}
				else
					{
						std::string result = "0";
						server->writeBuffer(0, result);
					}

				server->writeOutput();
				
				return enable;
			}
			
			case 13:
			{//return a users list
				std::cout << "\nList current users...\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"pack Users list in buffer\" operation.\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				std::string result = baseUsers->packUserListInBuffer(0);

				std::cout << result << "\n";

				//server->showBuff(30);
				//server->writeBuffer(0, result);
				server->writeOutput();

				return enable;
			}

			
			case 20:
			{//logIn

				std::cout << "Doing \"logIn\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				int n = server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"log in\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}
				
				//Read a user's pass that is in the buffer
				std::string pass;
				server->readBuffer(n, pass);
				std::cout <<"pass reconstruction: \"" << pass << "\"\n";

				//compose an answer
				int result = baseUsers->checkPass(login, pass);				
	
				server->clearBuffer();
				
				if(result == 1)
					{
						std::string result_find = "1";
						int start = server->writeBuffer(0, result_find);

						std::string name = baseUsers->packUserNameInBuffer(login,start);
						std::cout << "Name is: " << name << "\n";
						//server->writeBuffer(start, name);
						//server->showBuff(10);
																		
					}
				else
					{
						std::string result_find = "0";
						server->writeBuffer(0, result_find);
					}							

				server->writeOutput();

				return enable;
			}
			case 21:
			{
				//reconstruct "for all" message collection
				std::string login;
				server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"collection for all reconstruction\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				server->clearBuffer();
				std::string list = 	baseMsgAll->packAllMsgCOllectionInBuffer(0);
				std::cout << list << "\n";
				//server->writeBuffer(0, list);
				//server->showBuff(30);

				server->writeOutput();				

				return enable;
			}
			case 22:
			{//reconstruction pesonal message collection
				std::string login;
				server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Doing \"personal collection reconstruction\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				server->clearBuffer();
				std::string list = baseMsgPrs->packPrsMsgCollectionInBuffer(login, 0);
				std::cout << list << "\n";
				//server->writeBuffer(0, list);
				//server->showBuff(30);

				server->writeOutput();

				return enable;
			}

			case 23:
			{//send message to all other users

				std::string name;
				int start = server->readBuffer(0, name);
				std::cout <<"Name reconstruction: \"" << name << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Have a \"message for common collection\" operation from \"" + name + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				std::cout << "Have a message to all other users\n";				

				//read the message text
				std::string inp_text;				
				server->readBuffer(start, inp_text, '#');
				std::cout <<"text reconstruction: \"" << inp_text << "\"\n";
								
				//put message in the database
				baseMsgAll->addMessage(name, inp_text);
				
				return enable;
			}

			case 24:
			{//send message to a defined user"

				std::string name;
				int start = server->readBuffer(0, name);
				std::cout <<"Name reconstruction: \"" << name << "\"\n";
				
				std::cout << "Have a message to a particular users\n";			

				//read a text of the message			
				std::string inp_text;				
				start = server->readBuffer(start, inp_text, '#');
				std::cout <<"Text reconstruction: \"" << inp_text << "\"\n";
				
				//Read a name of a sender
				std::string to;	
				server->readBuffer(start, to);
				std::cout <<"Recepient by reconstruction: \"" << to << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Have a \"message personal message\" from \"" + name + "\" to \"" + to + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				//put message in the database
				baseMsgPrs->addMessage(name, to, inp_text);				

				return enable;
			}

			case 25:
			{//read message from "for all" collection

				std::string login;
				int n = server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Read a \"message from common collection\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				std::cout << "Reading a massage from collection to all\n";
				std::string mess_num;				

				//read from a buffer
				server->readBuffer(n, mess_num);
				std::cout <<"constructed nubmer of a message by string: \"" << mess_num << "\"\n";

				int n_mess_num = server->transformInNumber(mess_num);
			
				server->clearBuffer();
				std::string result = baseMsgAll->packMsgInBuffer(n_mess_num, 0);
				std::cout << result << "\n";
				//server->writeBuffer(0, result);
				//server->showBuff(30);

				server->writeOutput();
				

				return enable;
			}

			case 26:
			{//read message from a personal user's collection

				std::string login;
				int n = server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				{
					//put a line in log
					std::string logString = server->currentTimeDate();
					logString += "Read a \"message from personal collection\" operation for \"" + login + "\".\n";
            		Logger log(server->logFile);
            		log.writeLog(logString);
				}

				std::cout << "Reading a massage from a personal collection\n";
				std::string mess_num;				

				//read from a buffer
				server->readBuffer(n, mess_num);
				std::cout <<"constructed nubmer of a message by string: \"" << mess_num << "\"\n";

				int n_mess_num = server->transformInNumber(mess_num);
			
				server->clearBuffer();

				std::string result = baseMsgPrs->packMsgInBuffer(n_mess_num, 0);
				std::cout << result << "\n";
				//server->writeBuffer(0, result);
				//server->showBuff(30);

				server->writeOutput();

				return enable;
			}
			
			case 27:
			{//enter personal mode to change name or password
				std::string login;
				int n = server->readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				bool in_personal = true;//validate to stay in personal changing menu
				while (in_personal)
				{	
					//geting a right position to read from a buffer
					int start = 4 + login.size();
					int input_p = server->atBuff(start) - '0';
					std::cout << "Have an input " << input_p << "\n";

					switch (input)
					{
						case 1://change users name
						{		
							std::cout << "Changing user's name...\n";
							std::string new_name;
							start -= 1;
							server->readBuffer(start, new_name);
							
							baseUsers->changeName(login, new_name);

							{
								//put a line in log
								std::string logString = server->currentTimeDate();
								logString += "User\""+ login + "\"changed their name \n";
            					Logger log(server->logFile);
            					log.writeLog(logString);
							}
							
							in_personal = false;
							break;				
						}

						case 2://change users password
						{
							std::cout << "Changing user's password...\n";
							std::string new_pass;					
							start -= 1;
							server->readBuffer(start, new_pass);

							baseUsers->changePass(login, new_pass);

							{
								//put a line in log
								std::string logString = server->currentTimeDate();
								logString += "User\""+ login + "\"changed their pass\n";
            					Logger log(server->logFile);
            					log.writeLog(logString);
							}
							
							in_personal = false;	
							break;	
						}
						/*
						case 3://quit personal changing mode
						{
							std::cout << "Exiting personal changing mode...\n";
							in_personal = false;
							break;
						}
						*/
						default:
						{
							in_personal = false;
							break;
						}

					}
				}
				

				return enable;
			}

			default: return enable;
	
		}	
	
}




