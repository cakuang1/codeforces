#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int m;
    cin >> n >> m;

    ll sumB = 0;
    bool headReset = true;  // head always has A=0 baseline

    while(m--){
        int t;
        cin >> t;
        if(t==1){
            ll k;
            cin >> k;
            // new head arrives; its A=0
            headReset = true;
        }
        else if(t==2){
            ll k;
            cin >> k;
            // tail grows; head unchanged
        }
        else {
            ll b,s;
            cin >> b >> s;
            sumB += b;
        }
        // After every event, min is at car 1 with A = sumB
        cout << 1 << " " << sumB << "\n";
    }
    return 0;
}
