#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

string solution(string s) {
    string answer = "";
    stringstream ss(s);
    
    int mn = 1e9;
    int mx = -1e9;
    int num;
    while(ss >> num){
        cout << "mx " << mx << "mn " << mn << "num " << num << '\n'; 
        if(num < mn)
            mn = num;
        if (num > mx)
            mx = num;
    }
    
    answer = to_string(mn) + ' ' + to_string(mx);
    return answer;
}