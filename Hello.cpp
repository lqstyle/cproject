#include <iostream>
#include <string>
using namespace std;

// main() 是程序开始执行的地方

void getNext(int* next, const string &s){

  int j=0;
  next[0]=0;

  for(int i =1; i<s.size();i++){
    while(j>0 && s[i]!=s[j]){
        j = next[j-1];
    }
    if(s[i] == s[j]){
        j++;
    }
    next[i] = j;
  }
}


int getSubstr(string &s1, string &s2){
    if(s2.size()==0){
        return 0;
    }
   int j=0;
   int next[s2.size()];
   getNext(next, s2);

   for (int i = 0; i < s1.size(); i++)
   {
      while(j>0 && s1[i]!=s2[j]){
        j=next[j-1];
      }
      if(s1[i] == s2[j]){
        j++;
      }
      if(j==s2.size()){
         return i-s2.size()+1; 
      }
   }
   return -1;
   

}
int main(){
    cout << "Hello World"; // 输出 Hello World
    string s1 = "abcdabs";
    string s2= "abs";
    int position = getSubstr(s1,s2);
    cout << position;
    return 0; 
} 
