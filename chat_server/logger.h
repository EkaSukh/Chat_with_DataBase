#include <iostream>
#include <fstream>
#include <thread>
#include <shared_mutex>

class Logger{

    public:
    Logger(const std::string& file);
    ~Logger();    

    //work with log file
    void writeLog(const std::string& str);
    std::string readLog(int n);  
    
    //show last read line
    std::string readRes();  

    private:
    //variables to work with file
    std::string fileName;    
    std::fstream fs;

    //variable that keeps the line read from the log file
    std::string res;
    
    //mutex variable
    std::shared_mutex shrMutex;  

    //inner core functions to pass to std::thread t()
    void writeInFile(const std::string& str);
    void readFromFile(int n);
};
