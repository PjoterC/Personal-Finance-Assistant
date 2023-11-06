#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;
class Date
{
    public:
        Date(int day = 1, int month = 1, int year = 1);
        ~Date();
        Date& operator=(const Date& other);
        int day;
        int month;
        int year;
        friend std::ostream& operator<<(std::ostream& os, const Date& date);


    protected:

    private:

};

#endif // DATE_H
