/**
 * Implement a class Date. This class must meet the following requirements:
it has three private attributes to represent day, month and year
use a scoped enum for month
it has the following public functions:
it has a constructor that takes as arguments a day, a month and a year.
 (Forget about the validation for now)
it has a day() function that returns the day
it has a month() function that returns the month
it has a year() function that returns the year
it has a function add_days(const unsigned int n) which adds n days.
You have to take care to increment months and years accordingly (neglect leap years)
 */


#include "Date.h"
#include <iostream>

 Date::Date(const unsigned short day, const mymonths month, const int year)
 {
     dday = day;
     mmonth = month;
     yyear = year;

     ddays_per_month = {
         { mymonths::january ,   31},
         { mymonths::february ,  is_leap() ? 29 : 28},
         { mymonths::march ,     31},
         { mymonths::april ,     30},
         { mymonths::may ,       31},
         { mymonths::june ,      30},
         { mymonths::july ,      31},
         { mymonths::august ,    31},
         { mymonths::september , 30},
         { mymonths::october ,   31},
         { mymonths::november ,  30},
         { mymonths::december ,  31},
     };
 }

 const unsigned short Date::day() const
 {
     return dday;
 }

 const mymonths Date::month() const
 {
     return mmonth;
 }

 const unsigned int Date::year() const
 {
     return yyear;
 }

 void Date::add_one_day()
 {
     if (dday != ddays_per_month[mmonth])
     {
         dday = 1;
         if (mmonth == mymonths::december)
         {
             mmonth = mymonths::january;
             ++yyear;
         }
         else
         {
             int mth = static_cast<int>(mmonth);
             ++mth;
             mmonth = static_cast<mymonths>(mth);
         }
     }
     else
     {
         ++dday;
     }
 }




 const void Date::add_days(const unsigned int n)
 {
     for(unsigned int i = 0; i < n; ++i)
     {
         add_one_day();
     }
 }

 const bool Date::is_leap() const
 {
     return yyear % 4 == 0 && yyear % 400 != 0;
 }

 std::ostream& operator<<(std::ostream& os, const Date& d)
 {
   os << d.day() << " " << static_cast<int>(d.month()) << " " << d.year();
   return os;
 }

 bool operator==(const Date& lhs, const Date& rhs)
 {
     return lhs.day() == rhs.day() &&
            lhs.month() == rhs.month() &&
            lhs.year() == rhs.year();
 }

 bool operator!=(const Date& lhs, const Date& rhs)
 {
     return lhs.day() != rhs.day() ||
            lhs.month() != rhs.month() ||
            lhs.year() != rhs.year();
 }
