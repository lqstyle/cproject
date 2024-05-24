#include <iostream>
#include <map>
#include <string>
using namespace std;


int main(){
    
    std::map<int,string> persion;
    persion.insert(std::map<int,string> ::value_type(1,"lq"));
    persion.insert(pair < int,string > (2,"Jim"));

     std::map<int,string>::iterator it = persion.begin();
     std::map<int,string>::iterator itEnd = persion.end();
     while(it != itEnd){
        cout <<it->first << ' '<<it->second <<endl;
        it++;
     }


}
