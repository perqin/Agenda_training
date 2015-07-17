#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <ctime>
#include <string>

class Logger {
public:
    ~Logger();
    static Logger * getInstance();
    void logText(const char * s);
private:
    Logger();
    Logger(const Logger &);
    void operator=(const Logger &);
    static Logger * instance_;
    std::ofstream lout;
    std::time_t rawtime;
    struct std::tm * timeInfo;
};

#endif // LOGGER_H
