#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int MAXV = 1000000;
    vector<int> freq(MAXV + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
    }

    // count how many numbers are multiples of i
    vector<int> count(MAXV + 1);
    for (int i = 1; i <= MAXV; ++i)
        for (int j = i; j <= MAXV; j += i)
            count[i] += freq[j];

    // find largest i that divides at least two numbers
    for (int i = MAXV; i >= 1; --i)
        if (count[i] >= 2) {
            cout << i << "\n";
            break;
        }
}


// wegrate common rsdivisorw
// era werllwerpari srwer
// wedstmi hwrow hso slvshti wtr