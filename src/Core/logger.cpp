#include "logger.h"

Logger * Logger::instance_ = nullptr;

Logger * Logger::getInstance() {
    if (instance_ == nullptr)
        instance_ = new Logger();
    return instance_;
}

Logger::~Logger() {
    lout.close();
    instance_ = nullptr;
}

void Logger::logText(const char *s) {
    rawtime = time(NULL);
    timeInfo = localtime(&rawtime);
    char timeBuffer[20];
    strftime(timeBuffer, 20, "%Y-%m-%d/%H:%M:%S", timeInfo);
    lout << "[" << std::string(timeBuffer) << "]" << std::string(s) << std::endl;
}

Logger::Logger() {
    lout.open("./Agenda.log", std::ios_base::out | std::ios_base::app);
}
