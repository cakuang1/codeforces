#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    deque<int> dq;
    for(int i = 1; i <= n; i++){
        dq.push_back(i);
    }

    vector<int> removal;
    removal.reserve(n);

    while(!dq.empty()){
        // skip one child: move front to back
        int skip = dq.front(); dq.pop_front();
        dq.push_back(skip);

        // remove the next child
        int rem = dq.front(); dq.pop_front();
        removal.push_back(rem);
    }

    // print the removal order
    for(int i = 0; i < n; i++){
        cout << removal[i] << (i+1<n ? ' ' : '\n');
    }
    return 0;
}
