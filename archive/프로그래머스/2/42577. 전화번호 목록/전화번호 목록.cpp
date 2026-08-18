#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    unordered_set <string> s;
    for (auto& p : phone_book) {
        s.insert(p);
    }

    for (auto& p : phone_book) {
        for (int i = 1; i < p.size(); i++) {
            if (s.find(p.substr(0, i)) != s.end()) {
                answer = false;
                break;
            }
        }
        if (!answer)
            break;
    }
    return answer;
}