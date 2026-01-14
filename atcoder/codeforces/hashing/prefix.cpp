#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;

u64 rng64() {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return rng();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> A(N), B(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    // compress values so we can assign hashes
    vector<long long> vals;
    vals.insert(vals.end(), A.begin(), A.end());
    vals.insert(vals.end(), B.begin(), B.end());
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int M = vals.size();
    unordered_map<long long,int> idx;
    for (int i = 0; i < M; i++) idx[vals[i]] = i;

    vector<u64> H(M);
    for (int i = 0; i < M; i++) H[i] = rng64();

    vector<u64> sigA(N+1,0), sigB(N+1,0);
    vector<char> seenA(M,0), seenB(M,0);

    for (int i = 1; i <= N; i++) {
        int id = idx[A[i-1]];
        sigA[i] = sigA[i-1];
        if (!seenA[id]) {
            sigA[i] ^= H[id];
            seenA[id] = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        int id = idx[B[i-1]];
        sigB[i] = sigB[i-1];
        if (!seenB[id]) {
            sigB[i] ^= H[id];
            seenB[id] = 1;
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        cout << (sigA[x] == sigB[y] ? "Yes\n" : "No\n");
    }

    return 0;
}
 
// xor irfiacnairo nthat maximizes te number of colis na inexac we w
//  start fo the xoirificatiower

// can wrbe unique werly whashes w

// w w
// wxorificaniown we


// colum wner j has a uniqeu we1 ehas wer we werowi w
//  wer 
//  state wtha we rshows weup most often wacross all chocie we wer
//  whatw e
//w  xori erificaiotn wew w sthis wertae sw we

// how mayn wetimes wedo eshti apeeawe
// wexoriificator wgiven wthe  w
// detmeinr wtwh ehash we



// we