#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    // 자기 자신은 항상 케이스로 포함됨
    int answer = 1;
    for(int i=2;i < n ;i++){
        int sum = (i * (i + 1)) / 2;
        if((n - sum) % i == 0)
            answer++;
        
        if(sum >= n)
            break;
    }
    return answer;
}