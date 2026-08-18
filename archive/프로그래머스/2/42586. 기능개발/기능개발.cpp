#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int sz = progresses.size();
    bool check = false;
    vector<int> count(sz+1,0);
    while (!check) {
        check = true;
        for (int i = 0; i < sz; i++) {
            if (progresses[i] < 100) {
                check = false;
                progresses[i] += speeds[i];
                count[i]++;
            }
        }
    }
    int ans = 1;
    int mx = count[0];
    for (int i = 0; i < sz-1;i++) {
        if (mx >= count[i + 1]) {
            ans++;
        }
        else
        {
            answer.push_back(ans);
            ans = 1;
            mx = count[i + 1];
        }
    }
    answer.push_back(ans);
    return answer;
}