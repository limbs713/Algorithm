#include <string>
#include <vector>

using namespace std;

int dp[100001];

int fibo(int n){
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    if(dp[n] != 0)
        return dp[n];
    
    return dp[n] = (fibo(n-1) + fibo(n-2))% 1234567;
}

int solution(int n) {
    int answer = 0;
    answer = fibo(n);
    return answer;
}