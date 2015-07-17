#include "AgendaUI.h"
#include <functional>
#include "../Core/utils.h"

/*
 *  The following functions to display user interface should be in another
 *  class, and this will be implemented in Custom Edition.
 */

std::vector<std::string> getParams(unsigned n, std::string preOut = "") {
    std::string line;
    while (getline(std::cin, line), line.size() == 0)
        std::cout << preOut;
    std::vector<std::string> params = Utils::parseLine(line, ' ');
    if (params.size() < n)
        std::cout << preOut << "ERROR : Too few params";
    return params;
}

inline void displayLine(char c, unsigned n, bool newLine = false) {
    while (n-- > 0)
        std::cout << c;
    if (newLine)
        std::cout << std::endl;
}

void displayMenuItem(std::string item) {
    std::cout << "| " << item;
    displayLine(' ', 77 - item.size());
    std::cout << "|";
}

void displayHome() {
    std::cout << "+"; displayLine('-', 35); std::cout << " Agenda "; displayLine('-', 35); std::cout << "+";
    std::cout << "|"; displayLine(' ', 78); std::cout << "|";
    displayMenuItem("1 : Log in Agenda by user name and password");
    displayMenuItem("2 : Register an Agenda account");
    displayMenuItem("3 : About Agenda");
    displayMenuItem("4 : Quit Agenda");
    std::cout << "+"; displayLine('-', 78); std::cout << "+";
}

void displayAbout() {
    std::cout << "+"; displayLine('-', 32); std::cout << " Agenda About "; displayLine('-', 32); std::cout << "+";
    std::cout << "|  Agenda is a lite agenda client. You can manage your meeting timtable with   |";
    std::cout << "|  this handy but powerful tools. :P                                           |";
    std::cout << "|                 Agenda 0.0.2 released on 20150712 by Perqin                  |";
    std::cout << "|              Feedback : perqin@yeah.net || perqinxie@gmail.com               |";
    std::cout << "+"; displayLine('-', 78); std::cout << "+";
}

void displayCommand(bool logged = false, const std::string & un = "") {
    std::cout << std::endl;
    if (logged)
        std::cout << "Agenda@" << un << " : # ";
    else
        std::cout << "Agenda : $ ";
}

void displayUser(std::string userName) {
    std::cout << "+"; displayLine('-', 35); std::cout << " Agenda "; displayLine('-', 35); std::cout << "+";
    std::string welcome("Welcome, "); welcome += userName; welcome += "!"; if (welcome.size() % 2 == 1) welcome.push_back(' ');
    std::cout << "|"; displayLine(' ', (78 - welcome.size()) / 2); std::cout << welcome; displayLine(' ', (78 - welcome.size()) / 2); std::cout << "|";
    displayMenuItem(" 0 :    Help    - Show this list again");
    displayMenuItem(" 1 :  Meetings  - Create a meeting");
    displayMenuItem(" 2 :  Meetings  - List all meetings");
    displayMenuItem(" 3 :  Meetings  - List all sponsor meetings");
    displayMenuItem(" 4 :  Meetings  - List all particiapate meetings");
    displayMenuItem(" 5 :  Meetings  - Query meeting by title");
    displayMenuItem(" 6 :  Meetings  - Query meeting by time interval");
    displayMenuItem(" 7 :  Meetings  - Delete meeting by title");
    displayMenuItem(" 8 :  Meetings  - Delete all meetings");
    displayMenuItem(" 9 : My Profile - List all Agenda users");
    displayMenuItem("10 : My Profile - Delete my Agenda account");
    displayMenuItem("11 : My Profile - Log out");
    displayMenuItem("12 :    About   - About Agenda");
    std::cout << "+"; displayLine('-', 78); std::cout << "+";
}

AgendaUI::AgendaUI() : userName_(""), userPassword_("") {}

void AgendaUI::OperationLoop() {
    startAgenda();
    displayHome();
    std::string cmd;
    while (true) {
        displayCommand(agendaService_.userLogIn(userName_, userPassword_), userName_);
        cmd = getOperation();
        if (userName_ == "" && cmd == "4")
            break;
        if (!executeOperation(cmd))
            std::cout << "Unknown command, please input again!" << std::endl;
    }
    quitAgenda();
}

void AgendaUI::startAgenda() {
    agendaService_.startAgenda();
}

void AgendaUI::quitAgenda() {
    agendaService_.quitAgenda();
}

std::string AgendaUI::getOperation() {
    std::string c;
    std::cin >> c;
    return c; 
}

bool AgendaUI::executeOperation(std::string op) {
    if (op.size() > 2 || (op.at(0) < '0' || op.at(0) > '9') || (op.size() > 1 && (op.at(1) < '0' || op.at(1) > '9')))
        return false;
    int c = op.at(0) - '0';
    if (op.size() > 1)
        c = c * 10 + op.at(1) - '0';
    if (agendaService_.userLogIn(userName_, userPassword_)) {
        switch (c) {
            case 0: displayUser(userName_); break;
            case 1: createMeeting(); break;
            case 2: listAllMeetings(); break;
            case 3: listAllSponsorMeetings(); break;
            case 4: listAllParticipateMeetings(); break;
            case 5: queryMeetingByTitle(); break;
            case 6: queryMeetingByTimeInterval(); break;
            case 7: deleteMeetingByTitle(); break;
            case 8: deleteAllMeetings(); break;
            case 9: listAllUsers(); break;
            case 10: deleteUser(); break;
            case 11: userLogOut(); break;
            case 12: displayAbout(); break;
            default: break;
        }
    } else {
        switch (c) {
            case 1: userLogIn(); break;
            case 2: userRegister(); break;
            case 3: displayAbout(); break;
            default: break;
        }
    }
    return true;
}

void AgendaUI::userLogIn() {
    std::cout << "(Log in) [User name] [Password]" << std::endl;
    std::vector<std::string> params = getParams(2, "(Log in) ");
    if (params.size() < 2)
        return;
    if (agendaService_.userLogIn(params.at(0), params.at(1))) {
        std::cout << "(Log in) Successfully log in!" << std::endl;
        userName_ = params.at(0);
        userPassword_ = params.at(1);
        displayUser(params.at(0));
    } else
        std::cout << "(Log in) ERROR : Incorrect userName or password" << std::endl;
}

void AgendaUI::userRegister() {
    std::cout << "(Register) [User name] [Password] [Email] [Phone]" << std::endl;
    std::vector<std::string> params = getParams(4, "(Register) ");
    if (params.size() < 4)
        return;
    if (agendaService_.userRegister(params.at(0), params.at(1), params.at(2), params.at(3))) {
        std::cout << "(Register) Successfully register!" << std::endl;
        userName_ = params.at(0);
        userPassword_ = params.at(1);
        std::cout << "(Log in) Successfully log in!" << std::endl;
        displayUser(userName_);
    } else
        std::cout << "(Register) ERROR : Register fail!" << std::endl;
}

void AgendaUI::userLogOut() {
    userName_ = "";
    userPassword_ = "";
    displayHome();
}

void AgendaUI::deleteUser() {
    std::cout << "(Unregister) Are you sure to unregister your account? All meetings related to you with be deleted at the same time!" << std::endl;
    std::cout << "(Unregister) Y/n" << std::endl;
    std::string str;
    std::cin >> str;
    if (str == "Y") {
        if (agendaService_.deleteUser(userName_, userPassword_)) {
            std::cout << "(Unregister) Your account has been unregistered successfully! Now you are logged out." << std::endl;
            userLogOut();
        } else
            std::cout << "(Unregister) ERROR : Failed to unregister your account!" << std::endl;
    }
}

void AgendaUI::listAllUsers() {
    std::list<User> allUsers = agendaService_.listAllUsers();
    // TODO : make it tidier ok?
    std::cout << "User Name\tEmail\tPhone Number" << std::endl;
    for (std::list<User>::iterator it = allUsers.begin(); it != allUsers.end(); ++it)
        std::cout << it->getName() << "\t" << it->getEmail() << "\t" << it->getPhone() << std::endl;
}

void AgendaUI::createMeeting() {
    std::cout << "(Create meeting) [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << std::endl;
    std::vector<std::string> params = getParams(4, "(Create meeting) ");
    if (params.size() < 4)
        return;
    if (agendaService_.createMeeting(userName_, params.at(0), params.at(1), params.at(2), params.at(3)))
        std::cout << "(Create meeting) Successfully create meeting " << params.at(0) << "!" << std::endl;
    else
        std::cout << "(Create meeting) ERROR : Failed to create meeting!" << std::endl;
}

void AgendaUI::listAllMeetings() {
    std::cout << "(List all meetings)" << std::endl << std::endl;
    printMeetings(agendaService_.listAllMeetings(userName_));
}

void AgendaUI::listAllSponsorMeetings() {
    std::cout << "(List all sponsor meetings)" << std::endl << std::endl;
    printMeetings(agendaService_.listAllSponsorMeetings(userName_));
}

void AgendaUI::listAllParticipateMeetings() {
    std::cout << "(List all particiapate meetings)" << std::endl << std::endl;
    printMeetings(agendaService_.listAllParticipateMeetings(userName_));
}

void AgendaUI::queryMeetingByTitle() {
    std::cout << "(Query meeting) [title]" << std::endl;
    std::vector<std::string> params = getParams(1, "(Query meeting) ");
    if (params.size() < 1)
        return;
    std::cout << "Title\tSponsor\tParticipator\tStart Time\tEnd Time" << std::endl;
    printMeetings(agendaService_.meetingQuery(userName_, params.at(0)));
}

void AgendaUI::queryMeetingByTimeInterval() {
    std::cout << "(Query meetings) [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]:" << std::endl;
    std::vector<std::string> params = getParams(2, "(Query meetings) ");
    if (params.size() < 2)
        return;
    printMeetings(agendaService_.meetingQuery(userName_, params.at(0), params.at(1)));
}

void AgendaUI::deleteMeetingByTitle() {
    std::cout << "(Delete meeting) [title]" << std::endl;
    std::vector<std::string> params = getParams(1, "(Delete meeting) ");
    if (params.size() < 1)
        return;
    if (agendaService_.deleteMeeting(userName_, params.at(0)))
        std::cout << "(Delete meeting) " << params.at(0) << " has been deleted successfully!" << std::endl;
    else
        std::cout << "(Delete meeting) ERROR : Delete meeting fail!" << std::endl;
}

void AgendaUI::deleteAllMeetings() {
    std::cout << "(Delete all meetings) Are you sure to delete all meetings related to you?" << std::endl;
    std::cout << "(Delete all meetings) Y/n" << std::endl;
    std::string str;
    std::cin >> str;
    if (str == "Y") {
        if (agendaService_.deleteAllMeetings(userName_))
            std::cout << "(Delete all meetings) Delete all meetings successfully!" << std::endl;
        else
            std::cout << "(Delete all meetings) ERROR : Failed to delete all meetings!" << std::endl;
    }
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    if (meetings.size() == 0) {
        std::cout << "Oops! There is no meeting that matches your query." << std::endl;
        return;
    }
    std::function<std::string(std::string, unsigned)> parseItem = [](std::string s, unsigned n)->std::string {
        if (s.size() > n)
            return s.substr(0, n - 3) + "...";
        std::string res = s, space;
        if ((n - res.size()) % 2 == 1)
            res += " ";
        unsigned spaceNum = (n - res.size()) / 2;
        while (spaceNum-- > 0)
            space.push_back(' ');
        return space + res + space;
    };
    std::cout << "       Title           Sponsor   Participator   Start Time         End Time   " << std::endl;
    for (std::list<Meeting>::iterator it = meetings.begin(); it != meetings.end(); ++it)
        std::cout << parseItem(it->getTitle(), 19) << " "
                  << parseItem(it->getSponsor(), 12) << " "
                  << parseItem(it->getParticipator(), 12) << " "
                  << Date::dateToString(it->getStartDate()) << " "
                  << Date::dateToString(it->getEndDate()) << std::endl;
}
