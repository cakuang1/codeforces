#include <bits/stdc++.h>
using namespace std;

int main(){
    long long y, x;
    cin >> y >> x;
    // 1-based → 0-based xor:
    cout << ((y-1) ^ (x-1)) << "\n";
    return 0;
}

