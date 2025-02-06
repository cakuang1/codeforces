#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define EPS (1e-7)
#define INF (1e9)
#define PI (acos(-1))
//const ll mod = 1000000007;

int main() {
    //cout.precision(10);
    int n;
    cin >> n;
    int x[105], y[105], h[105];
    for(int i = 1; i <= n; i++){
        cin >> x[i] >> y[i] >> h[i];
        if(h[i] > 0){
            swap(x[i], x[1]);
            swap(y[i], y[1]);
            swap(h[i], h[1]);
        }
    }
    for(int cx = 0; cx <= 100; cx++){
        for(int cy = 0; cy <= 100; cy++){
            int ch = h[1] + abs(cx - x[1]) + abs(cy - y[1]);
            bool checker = true;
            for(int i = 2; i <= n; i++){
                if(max(ch - abs(x[i] - cx) - abs(y[i] - cy), 0) != h[i]){
                    checker = false;
                }
            }
            if(checker){
                cout << cx << " " << cy << " " << ch << endl;
                return 0;
            }
        }
    }
    return 0;
}
