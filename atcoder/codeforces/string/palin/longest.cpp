#include <bits/stdc++.h>
using namespace std;

vector<int> m;

struct Node {
    int len;                        
    int link;                       
    map<char,int> next;             
    Node(int l = 0) : len(l), link(0) {}
};

struct Eertree {
    string s;
    vector<Node> tree;
    int suff;

    Eertree(int n) {
        tree.reserve(n+5);
        tree.push_back(Node(-1));   // node 0
        tree.push_back(Node(0));    // node 1
        tree[0].link = 0;
        tree[1].link = 0;
        suff = 1;                   
    }

    void addChar(char c) {
        s.push_back(c);
        int pos = (int)s.size() - 1;

        int cur = suff;
        while (true) {
            int curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == c) break;
            cur = tree[cur].link;
        }

        m.push_back(tree[cur].len + 2);

        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            return;
        }
        
        int newnode = (int)tree.size();
        tree.push_back(Node(tree[cur].len + 2));
        tree[cur].next[c] = newnode;
        
        if (tree[newnode].len == 1) {
            tree[newnode].link = 1; 
        } else {
            int linkcand = tree[cur].link;
            while (true) {
                int candlen = tree[linkcand].len;
                if (pos - 1 - candlen >= 0 && s[pos - 1 - candlen] == c) {
                    tree[newnode].link = tree[linkcand].next[c];
                    break;
                }
                linkcand = tree[linkcand].link;
            }
        }

        suff = newnode;
    }
}; 

int main() {
    string str;
    cin >> str;
    int n = str.size(); 
    Eertree e(n);
    for (char c : str) e.addChar(c);
    int l = 1; 
    int end = 0;
    for (int i = 0 ; i < n; i++) {
        if (m[i] > l) {
            end = i; 
            l = m[i]; 
        }
    }
    
    int start = end - l + 1;
    cout << e.s.substr(start, l) << "\n";
}


// wre e wersure thsi weowevw seowkrs we