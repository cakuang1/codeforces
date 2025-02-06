#include <iostream>

using namespace std;
using ll = long long;

int main() {
    int a, b;
    cin >> a >> b;
    
    ll ret = 0;

    for (int i = b + 1; i <= a; i++) {
        for (int j = 0; j <= a / i; j++) {
            int nd = j * i;
            int am = min(a - nd + 1, i);
            int rm = max(0, am - b);

            ret += rm;
            if (rm && j == 0 && b == 0) {
                ret--;
            }
        }
    }

    cout << ret << endl;
    return 0;
}
