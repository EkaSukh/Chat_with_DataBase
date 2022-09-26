#include "logger.h"

Logger::Logger(const std::string& file): fileName(file)
{
    //open file in costructor
    fs.open(fileName, std::ios::app | std::ios::in);
     //create a file if it does not exist
     if(!fs.is_open())
     {
        fs.open(fileName, std::ios::out | std::ios::in);
     }
    
}

Logger::~Logger()
{
    //the close process is in destructor only
    fs.close();
}

//inner writing fuction to pass to std::thread t()
void Logger::writeInFile(const std::string& str)
{
    shrMutex.lock();
    fs << str;
    shrMutex.unlock();
}

//inner reading fuction to pass to std::thread t()
void Logger::readFromFile(int n)
{
    
    shrMutex.lock_shared();
    //read a selected line from the log file
    while(n != 0)
    {
        std::getline(fs, res);
        --n;
    }
        
    std::cout << res;
    shrMutex.unlock_shared();
   
}

//writing fuction
void Logger::writeLog(const std::string& str)
{
    std::thread t(&Logger::writeInFile, this, str);
    t.join();

}

//reading function
std::string Logger::readLog(int n)
{
    std::thread t(&Logger::readFromFile, this, n);
    t.join();
    
    return res;
}

//helping fuction that shows the last read line
std::string Logger::readRes()
{
    std::cout << "res: " << res << std::endl;

    return res;
}