#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map <string,int> s;
    for (auto& name : completion) {
        s[name]++;
    }

    for (auto& name : participant) {
        if (s[name] == 0)
            return name;
        --s[name];
    }

    return "";
}