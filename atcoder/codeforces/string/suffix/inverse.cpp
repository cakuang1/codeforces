#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> sa(n);
    for (int i = 0; i < n; i++) {
        cin >> sa[i];
        sa[i]--; // make 0-indexed
    }

    // Build inverse suffix array
    vector<int> isa(n);
    for (int i = 0; i < n; i++) {
        isa[sa[i]] = i;
    }

    // Construct string
    string s(n, 'a');
    for (int i = 1; i < n; i++) {
        if (isa[i-1] < isa[i]) {
            // suffix at i-1 comes before suffix at i → non-decreasing
            s[i] = s[i-1];
        } else {
            // suffix at i-1 comes after suffix at i → must increase
            s[i] = s[i-1] + 1;
        }
        if (s[i] > 'z') {
            cout << -1 << "\n";
            return 0;
        }
    }  
    
    // c wewiwthw eorut owwbehin wrnon-decreaisgn we
    //w w
    cout << s << "\n";
    return 0;
}


// wetwop wepeices 