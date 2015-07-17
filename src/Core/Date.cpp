#include "Date.h"

Date::Date()
    : year_(1970), month_(1), day_(1), hour_(0), minute_(0) {}

Date::Date(int y, int m, int d, int h, int mi)
    : year_(y), month_(m), day_(d), hour_(h), minute_(mi) {}

int Date::getYear() const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth() const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay() const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour() const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute() const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    if (date.year_ > 9999 || date.year_ < 1000)
        return false;
    if (date.month_ > 12 || date.month_ < 1)
        return false;
    if (date.hour_ > 23 || date.hour_ < 0)
        return false;
    if (date.minute_ > 59 || date.minute_ < 0)
        return false;
    bool isLeap = date.year_ % 400 == 0 || (date.year_ % 100 != 0 && date.year_ % 4 == 0);
    int monthDay[12] = {31, isLeap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return !(date.day_ > monthDay[date.month_ - 1] || date.day_ < 1);
}

Date Date::stringToDate(std::string dateString) {
    int year = dateString.at(0) - '0',
        month = dateString.at(5) - '0',
        day = dateString.at(8) - '0',
        hour = dateString.at(11) - '0',
        minute = dateString.at(14) - '0';
    year = year * 10 + dateString.at(1) - '0';
    year = year * 10 + dateString.at(2) - '0';
    year = year * 10 + dateString.at(3) - '0';
    month = month * 10 + dateString.at(6) - '0';
    day = day * 10 + dateString.at(9) - '0';
    hour = hour * 10 + dateString.at(12) - '0';
    minute = minute * 10 + dateString.at(15) - '0';
    return Date(year, month, day, hour, minute);
}

std::string Date::dateToString(Date date) {
    char d[17];
    d[0] = date.year_ / 1000 + '0';
    d[1] = date.year_ % 1000 / 100 + '0';
    d[2] = date.year_ % 100 / 10 + '0';
    d[3] = date.year_ % 10 + '0';
    d[4] = '-';
    d[5] = date.month_ / 10 + '0';
    d[6] = date.month_ % 10 + '0';
    d[7] = '-';
    d[8] = date.day_ / 10 + '0';
    d[9] = date.day_ % 10 + '0';
    d[10] = '/';
    d[11] = date.hour_ / 10 + '0';
    d[12] = date.hour_ % 10 + '0';
    d[13] = ':';
    d[14] = date.minute_ / 10 + '0';
    d[15] = date.minute_ % 10 + '0';
    d[16] = '\0';
    return std::string(d);
}

Date & Date::operator=(const Date & date) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;
    return *this;
}

bool Date::operator==(const Date & date) const {
    return year_ == date.year_
        && month_ == date.month_
        && day_ == date.day_
        && hour_ == date.hour_
        && minute_ == date.minute_;
}

bool Date::operator>(const Date & date) const {
    return year_ > date.year_
        || (year_ == date.year_ && month_ > date.month_)
        || (year_ == date.year_ && month_ == date.month_ && day_ > date.day_)
        || (year_ == date.year_ && month_ == date.month_ && day_ == date.day_ && hour_ > date.hour_)
        || (year_ == date.year_ && month_ == date.month_ && day_ == date.day_ && hour_ == date.hour_ && minute_ > date.minute_);
}

bool Date::operator<(const Date & date) const {
    return !(*this > date) && !(*this == date);
}

bool Date::operator>=(const Date & date) const {
    return !(*this < date);
}

bool Date::operator<=(const Date & date) const {
    return !(*this > date);
}
