#include "net.h"

//constructor for localhos
ClientTCP::ClientTCP()
{    
    // adjust structure for the server    
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    buff_shift = 0;
    sockd = 0;
    connection = 0;
    bzero(buff, BUF_SIZE);
}

//constructor for difined IP
ClientTCP::ClientTCP(std::string &ip)
{     
    // adjust structure for the server
    const char *addr = ip.c_str();
    serveraddress.sin_addr.s_addr = inet_addr(addr);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    buff_shift = 0;  
    sockd = 0;
    connection = 0;
    bzero(buff, BUF_SIZE);  
}

//connection to the server
void ClientTCP::clientConnect()
{
    // create a socket and check the success
    sockd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockd < 0)
    {
        std::cout << "Socket creation failed\n";
        exit(1);
    }

    connection = connect(sockd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (connection < 0)
    {
        std::cout << "Failed connect to the server\n";
        exit(1);
    }

}

//read an answer from the server
void ClientTCP::readInput()
{
    //put server to listen and accept a message from a client
    //int bytes_read =;
    read(sockd, buff, BUF_SIZE);
    //std::cout << "received " << bytes_read << " bytes.\n";
}

//read information from the buffer
int ClientTCP::readBuffer(int start,  std::string &outcome, char s)
{
    while(buff[start+buff_shift] != s)
    {		
        outcome += buff[start+buff_shift];
        ++start;
    }
    
    return ++start;
}

//reach a particular position in buffer
char ClientTCP::atBuff(int n)
{
    return buff[n];
}

//put information in the buffer
int ClientTCP::writeBuffer(int start, const std::string &outcome, char s)
{
    std::copy(outcome.begin(),outcome.end(),buff + start);
	start += outcome.size();
	buff[start] = s;
	++start;

    return start;
}

void ClientTCP::clearBuffer()
{
    bzero(buff, BUF_SIZE);

}

//send information to the server
void ClientTCP::writeOutput()
{
    //int sent_bytes = 
    send(sockd, buff, BUF_SIZE, 0);
    //std::cout << "Sent " << sent_bytes << " bytes.\n";
}

//helping debug function
void ClientTCP::showBuff(const int n)
{
    for(int k = 0; k < n; ++k)
    {
        std::cout << "symbol " << k << " is " << buff[k] << "\n";
    }
}