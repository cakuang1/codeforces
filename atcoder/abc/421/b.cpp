#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<long long> a(10);
    cin >> a[0] >> a[1];
    for (int i = 2; i < 10; i++) {
        string s = to_string(a[i - 2] + a[i - 1]); 

        reverse(s.begin() ,s.end());

        a[i] = stoll(s); 
    }
    cout << a[9] << endl;
}


