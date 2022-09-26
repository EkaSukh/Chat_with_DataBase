PREFIX = /usr/local/bin

chat: main.cpp lib
	g++ -std=c++17 -I/usr/include/mysql -o chat main.cpp -L. -lChat -lmysqlclient -pthread

lib: net.h net.cpp Interface.h Interface.cpp dataBase.h dataBase.cpp dbUsers.h dbUsers.cpp dbMsgAll.h dbMsgAll.cpp dbMsgPrs.h dbMsgPrs.cpp
	g++ -std=c++17 -o netLib.o net.cpp -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o dataBaseLib.o dataBase.cpp -lmysqlclient -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o dbUsersLib.o dbUsers.cpp -lmysqlclient -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o dbMsgAllLib.o dbMsgAll.cpp -lmysqlclient -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o dbMsgPrsLib.o dbMsgPrs.cpp -lmysqlclient -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o InterfLib.o Interface.cpp -lmysqlclient -pthread -c
	g++ -std=c++17 -I/usr/include/mysql -o loggerLib.o logger.cpp -pthread -c
	ar rc libChat.a netLib.o  InterfLib.o dataBaseLib.o dbUsersLib.o dbMsgAllLib.o dbMsgPrsLib.o loggerLib.o

clean:
	rm *.o *.a

install:
	install ./chat $(PREFIX)

uninstal:
	rm -rf $(PREFIX)/chat
