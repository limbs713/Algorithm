#include <string>
#include <vector>
#include <iostream>

using namespace std;

string make_binary(int sz){
    if(sz == 1) return "1";
    
    string result= "";
    while(sz > 0){
        result += (sz % 2 ? "1" : "0");
        sz /= 2;
    }
    
    return result;
}

vector<int> solution(string s) {
    vector<int> answer;
    int cnt = 0;
    int zero = 0;
    while(s != "1")
    {
    string newStr="";
    for(char iter : s){
        if(iter == '1'){
            newStr += iter;
        }
        else{
            zero++;
        }
    }
    s = newStr;
    s = make_binary(s.size());
    cnt++;
    }
    answer.push_back(cnt);
    answer.push_back(zero);
    
    return answer;
}