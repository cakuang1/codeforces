#include <iostream>
using std::cin;
using std::cout;

int main (void) {
	int x, c;
	cin >> x >> c;

	int cnt = x / (1000 + c);
	int ans = cnt * 1000;
	
	cout << ans << "\n";
	
	return 0;
}
