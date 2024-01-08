#include <vector>
#include <unordered_set>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    int num = nums.size();
    unordered_set <int> s;
    for (int i = 0; i < num; i++) {
        if (s.find(nums[i]) == s.end()) {
            answer++;
            s.insert(nums[i]);
        }
        if (num / 2 == answer)
            break;
    }

    return answer;
}