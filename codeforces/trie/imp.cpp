#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    int cnt;
    Node() {
        memset(next, -1, sizeof(next));
        cnt = 0;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> S(N);
    for(int i = 0; i < N; i++) {
        cin >> S[i];
    }

    // Pre-allocate enough nodes: sum of lengths <= 5e5, plus root
    vector<Node> trie;
    trie.reserve(500000 + 5);
    trie.emplace_back();  // root = index 0

    // 1) Build the trie, counting passes
    for(int i = 0; i < N; i++){
        int cur = 0;
        trie[cur].cnt++;
        for(char c : S[i]){
            int d = c - 'a';
            if(trie[cur].next[d] == -1){
                trie[cur].next[d] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].next[d];
            trie[cur].cnt++;
        }
    }

    // 2) For each string, walk until cnt < 2
    vector<int> answer(N);
    for(int i = 0; i < N; i++){
        int cur = 0, lcp = 0;
        for(char c : S[i]){
            int d = c - 'a';
            int nxt = trie[cur].next[d];
            if(trie[nxt].cnt >= 2){
                lcp++;
                cur = nxt;
            } else {
                break;
            }
        }
        answer[i] = lcp;
    }

    // 3) Output
    ostringstream oss;
    for(int i = 0; i < N; i++){
        oss << answer[i] << "\n";
    }
    cout << oss.str();
    return 0;
}



// ai w