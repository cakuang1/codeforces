#include <bits/stdc++.h>
using namespace std;



struct Node {
    int len;                        // length of palindrome
    int link;                       // suffix link
    map<char,int> next;             // edges by character
    Node(int l = 0) : len(l), link(0) {}
};

// classic dp quesiotn wew w w\
// ware wwe syre this works wra whwo woud wu osulv esolve this we
// we



// w2 w wsubsisn qq

// nubmer of s sdisntcin tsubseuqnces weof preifx e
// wea ar w wwe srethi even werwors we? 
// w
//givnwea stirng yo uwcan weremova wean number of characers form weit wrw 

//  d oesthsi wwlearl wor kwand wer wehwo woudl yowu sevnw ewsovle hits e we

// hwo mayn wedifferenc strings w 

// siubstring rordewr w w
// how to wedetmeirn ww wer
// whatcan wer wesay wabout ww twall wesubtrsign wes stargin we wat w w
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

        // Step 1: find largest suffix-palindrome we can extend
        int cur = suff;
        while (true) {
            int curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == c) break;
            cur = tree[cur].link;
        }

        // Step 2: check if this extension already exists
        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            return;
        }

        // Step 3: create new node
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



int main() {
    string str = "ababa";
    Eertree e(str.size());

    for (char c : str) e.addChar(c);

    cout << "Distinct palindromes:\n";
    for (int i = 2; i < (int)e.tree.size(); i++) {
        cout << "Length " << e.tree[i].len << "\n";
    }
}


// detmiern wete 