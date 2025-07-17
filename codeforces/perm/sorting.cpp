#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}
    void add(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }
    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        // Make a sorted copy and check for duplicates
        vector<int> b = a;
        sort(b.begin(), b.end());
        bool hasDup = false;
        for(int i = 1; i < n; i++){
            if (b[i] == b[i-1]) {
                hasDup = true;
                break;
            }
        }
        if(hasDup){
            // With any duplicate, 3-cycles generate all parities → always YES
            cout << "YES\n";
            continue;
        }

        // All distinct → sorting is possible iff sorting-permutation is even
        // Compress values 0..n-1
        vector<int> p(n);
        for(int i = 0; i < n; i++){
            p[i] = int(lower_bound(b.begin(), b.end(), a[i]) - b.begin());
        }

        // Count inversions mod 2 with Fenwick
        Fenwick fw(n);
        ll inv = 0;
        for(int i = 0; i < n; i++){
            int x = p[i] + 1;           // 1-based Fenwick
            int le = fw.sum(x);         // how many ≤ x seen so far
            inv += (i - le);            // how many > x seen so far
            fw.add(x, 1);
        }

        cout << ((inv % 2 == 0) ? "YES\n" : "NO\n");
    }

    return 0;
}
