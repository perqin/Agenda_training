#include "utils.h"
#include "Date.h"

std::string Utils::parseValue(const std::string & str) {
    if (str.at(0) != '\"')
        return str;
    std::string result;
    for (unsigned i = 1; i < str.size() - 1; ++i)
        if (str[i] != '\"' || (str[i] == '\"' && i != str.size() - 2 && str[i + 1] == '\"'))
            result += str[i];
    return result;
}

std::vector<std::string> Utils::parseLine(const std::string & s, char separator) {
    std::vector<std::string> valueList;
    if (s.size() == 0)
        return valueList;
    bool inQuote = false;
    std::string::const_iterator si = s.begin(), sl = si, sr;
    while (true) {
        if (si == s.end() || (!inQuote && *si == separator)) {
            sr = si;
            valueList.push_back(parseValue(std::string(sl, sr)));
            if (si == s.end())
                break;
            sl = sr;
            ++sl;
        }
        if (*si == '\"')
            inQuote = !inQuote;
        ++si;
    }
    return valueList;
}

bool Utils::validateDate(const std::string & d) {
    if (d.size() != 16)
        return false;
    char lb[16] = {'0', '0', '0', '0', '-', '0', '0', '-', '0', '0', '/', '0', '0', ':', '0', '0'};
    char ub[16] = {'9', '9', '9', '9', '-', '9', '9', '-', '9', '9', '/', '9', '9', ':', '9', '9'};
    for (unsigned i = 0; i < 16; ++i)
        if (d.at(i) < lb[i] || d.at(i) > ub[i])
            return false;
    return Date::isValid(Date::stringToDate(d));
}
