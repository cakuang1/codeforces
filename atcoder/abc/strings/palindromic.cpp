#include <bits/stdc++.h>
using namespace std;

struct Eertree {
     struct Node {

        int len;
        int link;
        
        vector<int> next;

        Node(int _len  = 0) : len(_len), link(0) {
            next.fill(0);
        }
     };
       string s;
    vector<Node> tree;
    int last;
    int sz;

    Eertree(int maxLen = 0 ) {
        tree.resize(maxLen + 3);
        init(); 
    }
    void init(){
        s.clear();
        sz = 2;
        tree[0] = Node(-1);
        tree[0].link = 0;

        tree[1] = Node(0);
        tree[1].link = 0;

        last = 1;
    }
    int getLink(int v, int pos) {
        while (true) {
            int curLen = tree[v].len;
            if (pos - 1 - curLen >= 0 && s[pos - 1 - curLen] == s[pos]) {
                return v;
            }
            v = tree[v].link;
        }
    }
    bool addChar(char ch) {
        s += ch;
        int pos = (int)s.size() - 1;
        int c = ch - 'a';

        // Step 1: find largest suffix-palindrome A that can be extended
        int cur = getLink(last, pos);

        // Step 2: if xAx already exists, reuse it
        if (tree[cur].next[c]) {
            last = tree[cur].next[c];
            return false;
        }

        // how amnsstism this ewr siscewra
        // wewweroxdf sdodsl wer
        // werahc pfa,s sienwcom/ w
        int now = sz++;
        tree[now] = Node(tree[cur].len + 2);
        tree[cur].next[c] = now;

        if (tree[now].len == 1) {
            tree[now].link = 1;
        } else {
            int linkCand = getLink(tree[cur].link, pos);
            tree[now].link = tree[linkCand].next[c];
        }
        
        last = now;
        return true;
    }

}