#include "AgendaService.h"

AgendaService::AgendaService() {}

AgendaService::~AgendaService() {}

bool AgendaService::userRegister(std::string userName, std::string password, std::string email, std::string phone) {
    // TODO : Validation
    std::list<User> users = storage_->queryUser([&](const User & user) {
        return user.getName() == userName;
    });
    if (!users.empty()) {
        logger->logText("userRegister : The user name is already existed");
        return false;
    }
    storage_->createUser(User(userName, password, email, phone));
    storage_->sync();
    return true;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    std::list<User> users = storage_->queryUser([&](const User & user) {
        return user.getName() == userName && user.getPassword() == password;
    });
    if (users.size() != 1)
        logger->logText("userLogIn : Login failed");
    return users.size() == 1;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    if (!userLogIn(userName, password)) {
        logger->logText("deleteUser : The user is not logging in");
        return false;
    }
    storage_->deleteMeeting([&](const Meeting & meeting) {
        return meeting.getSponsor() == userName || meeting.getParticipator() == userName;
    });
    storage_->deleteUser([&](const User & user) {
        return user.getName() == userName;
    });
    storage_->sync();
    return true;
}
std::list<User> AgendaService::listAllUsers() {
    return storage_->queryUser([](const User &) { return true; });
}

bool AgendaService::createMeeting(
    std::string userName, std::string title, std::string participator,
    std::string startDate, std::string endDate) {
    if (!Utils::validateDate(startDate) || !Utils::validateDate(endDate)
        || Date::stringToDate(startDate) >= Date::stringToDate(endDate)) {
        logger->logText("createMeeting : The given dates are invalid");
        return false;
    }
    if (userName == participator) {
        logger->logText("createMeeting : The participator should not be the same people as the sponsor");
        return false;
    }
    if (storage_->queryUser([&](const User & user) {
        return user.getName() == userName;
    }).empty()) {
        logger->logText("createMeeting : The sponsor is not in the users list");
        return false;
    }
    if (storage_->queryUser([&](const User & user) {
        return user.getName() == participator;
    }).empty()) {
        logger->logText("createMeeting : The participator is not in the users list");
        return false;
    }
    if (storage_->queryMeeting([&](const Meeting & meeting) {
        return meeting.getTitle() == title;
    }).size() > 0) {
        logger->logText("createMeeting : A meeting with the same title has already existed");
        return false;
    }
    if (storage_->queryMeeting([&](const Meeting & meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName
            || meeting.getSponsor() == participator || meeting.getParticipator() == participator)
            && ((meeting.getEndDate() > Date::stringToDate(startDate)
                && meeting.getEndDate() < Date::stringToDate(endDate))
                || (meeting.getStartDate() > Date::stringToDate(startDate)
                && meeting.getStartDate() < Date::stringToDate(endDate))
                || (meeting.getStartDate() <= Date::stringToDate(startDate)
                    && meeting.getEndDate() >= Date::stringToDate(endDate)));
    }).size() > 0) {
        logger->logText("createMeeting : The sponsor or participator is not available during the given period");
        return false;
    }
    storage_->createMeeting(Meeting(userName, participator, 
        Date::stringToDate(startDate), Date::stringToDate(endDate), title));
    storage_->sync();
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    return storage_->queryMeeting([&](const Meeting & meeting) {
        return meeting.getTitle() == title && (meeting.getSponsor() == userName || meeting.getParticipator() == userName);
    });
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
std::string endDate) {
    std::list<Meeting> emptyList;
    if (!Utils::validateDate(startDate) || !Utils::validateDate(endDate)
        || Date::stringToDate(startDate) >= Date::stringToDate(endDate)) {
        logger->logText("meetingQuery : The given date s are invalid");
        return emptyList;
    }
    return storage_->queryMeeting([&](const Meeting & meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName)
            && ((meeting.getEndDate() >= Date::stringToDate(startDate)
                && meeting.getEndDate() <= Date::stringToDate(endDate))
                || (meeting.getStartDate() >= Date::stringToDate(startDate)
                && meeting.getStartDate() <= Date::stringToDate(endDate)));
    });
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting & meeting) {
        return meeting.getSponsor() == userName || meeting.getParticipator() == userName;
    });
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting & meeting) {
        return meeting.getSponsor() == userName;
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting & meeting) {
        return meeting.getParticipator() == userName;
    });
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    bool res = storage_->deleteMeeting([&](const Meeting & meeting) {
        return meeting.getSponsor() == userName && meeting.getTitle() == title;
    }) > 0;
    if (!res)
        logger->logText("deleteAllMeetings : No meeting to be deleted");
    storage_->sync();
    return res;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    bool res = storage_->deleteMeeting([&](const Meeting & meeting) {
        return meeting.getSponsor() == userName;
    }) > 0;
    if (!res)
        logger->logText("deleteAllMeetings : No meeting to be deleted");
    storage_->sync();
    return res;
}

void AgendaService::startAgenda() {
    storage_ = Storage::getInstance();
    logger = Logger::getInstance();
}
void AgendaService::quitAgenda() {
    storage_->sync();
    delete storage_;
    delete logger;
}
