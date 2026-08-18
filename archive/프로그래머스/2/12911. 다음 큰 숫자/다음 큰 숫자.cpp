#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int solution(int n) {
    int answer =0;
    vector <int> curr;
    
    while(n>0)
    {
        curr.push_back(n%2);
        n/=2;   
    }
    
    curr.push_back(0);
    reverse(curr.begin(),curr.end());
    next_permutation(curr.begin(),curr.end());
        
    for(int bit : curr) {
        answer = answer * 2 + bit;
    }
    
    return answer;
}