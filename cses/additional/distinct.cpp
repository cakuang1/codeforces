#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n+1);
    for(int i = 1; i <= n; i++){
        cin >> x[i];
    }

    unordered_map<int,int> last;
    last.reserve(n*2);

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        int p = last.count(x[i]) ? last[x[i]] : 0;
        ans += 1LL * (i - p) * (n - i + 1);
        last[x[i]] = i;
    }

    cout << ans << "\n";
    return 0;
}
