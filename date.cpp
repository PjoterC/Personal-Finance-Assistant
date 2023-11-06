#include "date.h"

Date::Date(int day, int month, int year)
{
    if(day < 1 || day > 31) throw day;
    if(month < 1 || month > 12) throw month;
    if(year < 0) throw year;
    if(day > 30 && (month%2 != 0)) throw day;
    if(day > 29 && month == 2 && (year%4) == 0) throw day;
    if(day > 28 && month == 2 && (year%4) != 0) throw day;
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::~Date()
{
    //dtor
}

Date& Date::operator=(const Date& other)
{
    if (this != &other)
    {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.day << endl << date.month << endl << date.year << endl;
    return os;
}


