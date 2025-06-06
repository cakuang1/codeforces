#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    vector<int> dist(K, INT_MAX);
    deque<int> q;

    int start = 1 % K;
    dist[start] = 0;
    q.push_front(start);

    while (!q.empty()) {
        int r = q.front(); q.pop_front();
        int d = dist[r];

        // multiply by 10 (cost 0)
        int r10 = (r * 10) % K;
        if (d < dist[r10]) {
            dist[r10] = d;
            q.push_front(r10);
        }

        // add 1 (cost 1)
        int r1 = (r + 1) % K;
        if (d + 1 < dist[r1]) {
            dist[r1] = d + 1;
            q.push_back(r1);
        }
    }

    // answer = # of +1-presses (dist[0]) PLUS one initial '1'
    cout << dist[0] + 1 << "\n";
    return 0;
}


