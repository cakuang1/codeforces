#include <bits/stdc++.h>
using namespace std;

struct Node {
	char val;
	int weight, size;
	Node *left, *right;
	Node(int num ) : val(num), weight(rand()), size(1), left(NULL), right(NULL) {}
} *root;

inline int size(Node *treap) { return treap ? treap->size : 0; }

void split(Node *treap, Node *&left, Node *&right, int val) {
	if (!treap) {
		left = right = NULL;
		return;
	}

	if (size(treap->left) < val) {
		split(treap->right, treap->right, right, val - size(treap->left) - 1);
		left = treap;
	} else {
		split(treap->left, left, treap->left, val);
		right = treap;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}

void merge(Node *&treap, Node *left, Node *right) {
	if (left == NULL) {
		treap = right;
		return;
	}
	if (right == NULL) {
		treap = left;
		return;
	}

	if (left->weight < right->weight) {
		merge(left->right, left->right, right);
		treap = left;
	} else {
		merge(right->left, left, right->left);
		treap = right;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}


// custom operators
ostream &operator<<(ostream &os, Node *n) {
	if (!n) return os;
	os << n->left;
	os << n->val;
	os << n->right;
	return os;
}   


// pareto frontier


// 2d queries 


// for all a in increasing worder 



int main()  { 
        ios_base::sync_with_stdio(0); cin.tie(0);  
        
        int q; cin >> q;            
        while (q --) {int a, b; cin >> a >> b; 
            we    
             
             
        }
        
                
         
        cout << root << endl; 
        return 0;
   }
    
    
    