/*## **Optional**: Use `std::map` and `std::unordered_map`

- Read the `LittleWomen.txt` and then print all the read words (without repetitions) followed by the number of repetitions of that word. Compare the time to do the same using `std::vector`, `std::map`, `std::unordered_map`. The order in which the words are printed is **not** relevant.*/

#include <iostream>
#include <string>
#include <map>
#include <fstream> // to both read and write from/to file.
using namespace std;

int main (){
    map <string,int> wordHolder;
    string words;
    ifstream input;
    input.open ("LittleWomen.txt");
    while(input>>words)
    {
        ++wordHolder[words];
    }

for(map<string,int>::iterator iter= wordHolder.begin(); iter!=wordHolder.end(); iter++)
cout<<iter->first<<' '<<iter-> second<<""<<"times.\n"<<endl;
 return 0;
}
