#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;


int main(void){
	string s;
	cin >> s;
	int sum = 0;
	int n = s.size();
	for (int i = n-1; i >= 0; i--) {
		int v = s[i] - '0';
		int u = ((i < n-1) ? (s[i+1] - '0') : 0);
		int b = (10 + v - u) % 10;
		sum += b;
	}
    int ans = sum + n;
	cout << ans << "\n";
    
    return 0;
}
