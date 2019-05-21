
#ifndef DATE_H__
#define DATE_H__
#include<map>

/**
   Defines the month type used inside the Date class
*/
enum class mymonths { january = 1,february,march,april,may,june,
                       july,august,september,october,november,december
                     };

class Date {

private:
   unsigned short dday;
   mymonths mmonth;
   int yyear;
   std::map<mymonths, unsigned char> ddays_per_month; // mapping months with total days in the month

   // used for public add_days method for one day
   void add_one_day();

public:
   Date(const unsigned short day, const mymonths month, const int year);

   const unsigned short day() const;
   const mymonths month() const;
   const unsigned int year() const;


    //adding n number of days to the current day
   //passing the number of days to add

   const void add_days(const unsigned int n);


   const bool is_leap() const; //returns true if current year is leap year
};

// Operators overloading
std::ostream& operator<<(std::ostream& os, const Date& d);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);



#endif
