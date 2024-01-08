#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    int sz = genres.size();
    map <string, int> sum;
    map <string, vector<int>> chart;

    for (int i = 0; i < sz; i++) {
        sum[genres[i]] += plays[i];
        chart[genres[i]].push_back(i);
    }
    vector<pair<string, int>> vec(sum.begin(), sum.end());

    sort(vec.begin(), vec.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
    for (auto& a : vec) {
            sort(chart[a.first].begin(), chart[a.first].end(),
                [plays](int first, int second)-> bool
                {
                    if (plays[first] != plays[second])
                        return plays[first] > plays[second];
                    else
                    {
                        return first < second;
                    }
                });
            answer.push_back(chart[a.first][0]);
            if(chart[a.first].size() > 1)
                answer.push_back(chart[a.first][1]);
    }
    return answer;
}   