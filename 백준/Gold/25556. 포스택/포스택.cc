#include <iostream>
#include <stack>
using namespace std;

int main() {
	int n;
	stack<int> s[4];
	cin >> n;

	for (int i = 0; i < n; i++) {
		int temp;
          cin >> temp;
                for (int j=0;j<4;j++) {
            if (s[j].empty() || s[j].top() < temp){
				s[j].push(temp);
				break;
			}
            else if (j!= 3) {
				continue;
			}
			else {
              cout << "NO" << '\n';
			  return 0;
			}
		  }
        }
        cout << "YES" <<'\n';
		return 0;


}