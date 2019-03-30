/*
write a function get_int that reads from stdin until a valid number is fed
write a function get_double that reads from stdin until a valid number is fed.
*/
#include<iostream>
#include "Getters.h"


void get_int()
{
    int input;
    std::cout<<"Enter an integer "<<endl;
    while(!(std::cin>>input))
    {
    std::cout<< "Please enter an integer: "<<endl;;
    std::cin.clear();
    std::cin.ignore();
    }
}


void get_double()
{
double input;
std::cout<<"Enter a double "<<endl;
while(!(std::cin>>input))
{   std::cout<< "Please enter a double: "<<endl;
    std::cin.clear();//After a wrong input clear the error flag from cin
    std::cin.ignore();//ignore what just read

}
}



/* AlTERNATIVE

void get_int(int input)
{
    bool bFail;
    do{
        std::cout<<"Please enter an integer: " <<std::endl;
        std::cin>>input;
        bFail=std::cin.fail();
        std::cin.clear();
        std::cin.ignore();
    }
    while(bFail==true);
}*/
