#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

class Utils {
public:
    static std::string parseValue(const std::string & str);
    static std::vector<std::string> parseLine(const std::string & s, char separator);
    static bool validateDate(const std::string & d);
};

#endif // UTILS_H
