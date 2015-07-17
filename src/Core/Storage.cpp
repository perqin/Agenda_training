#include "Storage.h"
#include "utils.h"

Storage * Storage::instance_ = nullptr;


Storage::Storage() {
    readFromFile("./");
}

bool Storage::readFromFile(const char * fpath) {
    bool ret = true;
    std::string fullUserName(fpath), fullMeetingName(fpath);
    fullUserName += "User.csv";
    fullMeetingName += "Meeting.csv";
    std::string str;
    std::vector<std::string> valueList;
    userList_.clear();
    meetingList_.clear();
    std::ifstream fin;
    fin.open(fullUserName);
    if (fin) {
        getline(fin, str);
        while (getline(fin, str)) {
            valueList = Utils::parseLine(str, ',');
            userList_.push_back(User(valueList.at(0), valueList.at(1), valueList.at(2), valueList.at(3)));
        }
    } else
        ret = false;
    fin.close();
    fin.open(fullMeetingName);
    if (fin) {
        getline(fin, str);
        while (getline(fin, str)) {
            valueList = Utils::parseLine(str, ',');
            meetingList_.push_back(Meeting(valueList.at(0), valueList.at(1), Date::stringToDate(valueList.at(2)), Date::stringToDate(valueList.at(3)), valueList.at(4)));
        }
    } else
        ret = false;
    fin.close();
    return ret;
}

bool Storage::writeToFile(const char * fpath) {
    std::string fullUserName(fpath), fullMeetingName(fpath);
    fullUserName += "User.csv";
    fullMeetingName += "Meeting.csv";
    std::function<std::string(const std::string &)> addComma = [](const std::string & str)->std::string {
        std::string result;
        result.push_back('\"');
        for (unsigned i = 0; i < str.size(); ++i)
            if (str.at(i) == '\"')
                result += "\"\"";
            else
                result.push_back(str.at(i));
        result.push_back('\"');
        return result;
    };
    std::ofstream fout;
    fout.open(fullUserName);
    fout << "\"Name\",\"Password\",\"Email\",\"Phone\"" << std::endl;
    for (std::list<User>::iterator it = userList_.begin(); it != userList_.end(); ++it) {
        fout << addComma(it->getName()) << ",";
        fout << addComma(it->getPassword()) << ",";
        fout << addComma(it->getEmail()) << ",";
        fout << addComma(it->getPhone()) << std::endl;
    }
    fout.close();
    fout.open(fullMeetingName);
    fout << "\"Sponsor\",\"Participator\",\"Start date\",\"End date\",\"Title\"" << std::endl;
    for (std::list<Meeting>::iterator it = meetingList_.begin(); it != meetingList_.end(); ++it) {
        fout << addComma(it->getSponsor()) << ",";
        fout << addComma(it->getParticipator()) << ",";
        fout << addComma(Date::dateToString(it->getStartDate())) << ",";
        fout << addComma(Date::dateToString(it->getEndDate())) << ",";
        fout << addComma(it->getTitle()) << std::endl;
    }
    fout.close();
    return true;
}

Storage * Storage::getInstance() {
    if (instance_ == nullptr)
        instance_ = new Storage();
    return instance_;
}

Storage::~Storage() {
    instance_ = nullptr;
}

void Storage::createUser(const User & user) {
    userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) {
    std::list<User> result;
    for (std::list<User>::iterator it = userList_.begin(); it != userList_.end(); ++it)
        if (filter(*it))
            result.push_back(*it);
    return result;
}

int Storage::updateUser(std::function<bool(const User &)> filter, std::function<void(User &)> switcher) {
    int result = 0;
    for (std::list<User>::iterator it = userList_.begin(); it != userList_.end(); ++it)
        if (filter(*it)) {
            switcher(*it);
            ++result;
        }
    return result;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int result = userList_.size();
    std::list<User>::iterator it = userList_.begin();
    while (it != userList_.end()) {
        if (filter(*it))
            userList_.erase(it++);
        else
            ++it;
    }
    return result - userList_.size();
}

void Storage::createMeeting(const Meeting & meeting) {
    meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) {
    std::list<Meeting> result;
    for (std::list<Meeting>::iterator it = meetingList_.begin(); it != meetingList_.end(); ++it)
        if (filter(*it))
            result.push_back(*it);
    return result;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter, std::function<void(Meeting &)> switcher) {
    int result = 0;
    for (std::list<Meeting>::iterator it = meetingList_.begin(); it != meetingList_.end(); ++it)
        if (filter(*it)) {
            switcher(*it);
            ++result;
        }
    return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int result = meetingList_.size();
    std::list<Meeting>::iterator it = meetingList_.begin();
    while (it != meetingList_.end()) {
        if (filter(*it))
            meetingList_.erase(it++);
        else
            ++it;
    }
    return result - meetingList_.size();
}

bool Storage::sync() {
    return writeToFile("./");
}
