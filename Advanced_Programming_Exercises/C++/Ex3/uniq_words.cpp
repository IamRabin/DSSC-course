
/*Avoid repeated words

- Read from stdin a sequence of words. Store each word in a `std::vector<std::string>`. Then, print the words without repetitions.*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm> //used for sorting
using namespace std;

int main()
{
 cout<<"Enter any words: "<<endl;
 string words;

 vector<string>stringHolder; // declaring vector of strings.


 while (cin>>words)
 {
    stringHolder.push_back(words);// appending one line at a time to the vector.
}
sort(stringHolder.begin(),stringHolder.end());
int vsize=stringHolder.size();

int count=1;
words=stringHolder[0];

for(int i=1;i<vsize;i++)
{
    if(words!=stringHolder[i])
    {
        cout<<count<<"  "<<words<<endl;
        count=0; //reset count to 0.
        words=stringHolder[i];
    }
    count++;
}
cout<<count<< "  " << words<< endl;
return 0;
}
