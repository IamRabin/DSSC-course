/*
    Write a code that reads a number with its proper unit of measure, and prints back that number according to the SI units */

#include<iostream>
#include<string>
#define x 0.0254
using namespace std;

void measurement_converter(double reading, string unit)
{
    if ( unit == "m")
    {
        cout<<"Reading in inch: "<<reading/x<<" "<<"inch"<<endl;
    }
    else if( unit == "in")
    {
        cout<<"Reading in meter:"<<reading * x<<" "<<"meter"<<endl;
    }
    else
    {

    cout<<"We only convert meter to inches and viceversa.Please check your units.";
    }
}

int main()
{
    double reading;
    string unit;
    cout<< "Enter the measurement : "<<endl;
    cin>>reading;
    cout<< "Enter the unit: "<<endl;
    cin>>unit;
    measurement_converter(reading,unit);
    return 0;
}
