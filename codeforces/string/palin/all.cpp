#include <bits/stdc++.h>
using namespace std;



struct Node {
    int len;                        // length of palindrome
    int link;                       // suffix link
    map<char,int> next;             // edges by character
    Node(int l = 0) : len(l), link(0) {}
};


struct Eertree {
    string s;
    vector<Node> tree;
    int suff;  // node representing the longest palindromic suffix so far

    Eertree(int n) {
        tree.reserve(n+5);

        // imaginary nodes
        tree.push_back(Node(-1));   // node 0: length -1
        tree.push_back(Node(0));    // node 1: length 0
        tree[0].link = 0;
        tree[1].link = 0;
        suff = 1;                   // empty string
    }

    void addChar(char c) {
        s.push_back(c);
        int pos = (int)s.size() - 1;

        //d oeshtis w
        // Step 1: find largest suffix-palindrome we can extend
        int cur = suff;
        while (true) {
            int curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == c) break;
            cur = tree[cur].link;
        }
        
        cout << tree[cur].len + 2 << ' '; 
        // Step 2: check if this extension already exists
        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            return;
        }

        // w
        int newnode = (int)tree.size();
        tree.push_back(Node(tree[cur].len + 2));
        tree[cur].next[c] = newnode;
        
        // Step 4: set suffix link
        if (tree[newnode].len == 1) {
            tree[newnode].link = 1; // single char -> link to empty string
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

// d iesht\
 


int main() {
    string str;
    cin >> str;
    Eertree e(str.size());
    for (char c : str) e.addChar(c);


}


// detmiern wete 