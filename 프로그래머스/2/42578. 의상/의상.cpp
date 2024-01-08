#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map <string, int> m;
    for (auto& elem : clothes) {
        m[elem[1]]++;
    }

    for (auto& e : m) {
        answer *= e.second + 1;
    }
    return --answer;
}