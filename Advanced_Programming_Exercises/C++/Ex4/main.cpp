#include "Date.h"
#include <iostream>

// Tests for the Date class
int main()
{
    Date D1 = Date(1, month_enum::october, 2005);
    Date D2 = Date(10, month_enum::october, 2017);
    Date D3 = Date(25, month_enum::november, 2018);
    Date D4 = Date(30, month_enum::february, 2400);
    Date D5 = Date(12, month_enum::february, 2015);
    D1 == D1 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    D1 == D2 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    D4 == D5 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;

    D4.is_leap() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    D5.is_leap() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    D4.add_days(1);
    std::cout << D4 << std::endl;
    D5.add_days(1);
    std::cout << D5 << std::endl;
    D1.add_days(18);
    std::cout << D1 << std::endl;
    return 0;
}
