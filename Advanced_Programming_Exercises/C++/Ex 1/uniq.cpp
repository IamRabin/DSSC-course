/**
uniq
 Write a simple version of the Unix program uniq -c, which, when fed with a text,
 outputs the same text with consecutive identical lines collapsed to one prepended
 with the number of repetitions
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm> //used for sort
using namespace std;

int main()
{
 cout<<"Enter any texts: "<<endl;
 string lines;

 vector<string>stringHolder; // declaring vector of strings.


 while (getline(cin,lines))
 {
    stringHolder.push_back(lines);// appending one line at a time to the vector.
}
sort(stringHolder.begin(),stringHolder.end());
int vsize=stringHolder.size();

int count=1;
lines=stringHolder[0];

for(int i=1;i<vsize;i++)
{
    if(lines!=stringHolder[i])
    {
        cout<<count<<"  "<<lines;
        count=0; //reset count to 0.
        lines=stringHolder[i];
    }
    count++;
}
cout<<count<< "  " << lines << "/n";
return 0;
}
