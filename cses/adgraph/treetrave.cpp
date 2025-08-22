#include <bits/stdc++.h>
using namespace std;

struct Frame {
    bool isLeaf;
    int pre_l, pre_r, in_l, in_r;
    int root;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> preorder(n), inorder(n), pos(n+1);
    for (int i = 0; i < n; i++) {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
        pos[inorder[i]] = i;
    }

    vector<int> post;
    post.reserve(n);
    vector<Frame> st;
    st.reserve(2*n);

    // initial frame: the whole tree
    st.push_back({false, 0, n, 0, n, 0});

    while (!st.empty()) {
        Frame f = st.back();
        st.pop_back();

        if (f.isLeaf) {
            // output the root
            post.push_back(f.root);
            continue;
        }
        // range frame
        int pl = f.pre_l, pr = f.pre_r;
        int il = f.in_l, ir = f.in_r;
        if (pl >= pr) continue;
        int root = preorder[pl];
        int idx = pos[root];
        int left_size = idx - il;
        // push root for postorder after children
        st.push_back({true, 0,0,0,0, root});
        // right subtree: preorder [pl+1+left_size, pr), inorder [idx+1, ir)
        int rp_l = pl + 1 + left_size, rp_r = pr;
        int ri_l = idx + 1, ri_r = ir;
        if (rp_l < rp_r) {
            st.push_back({false, rp_l, rp_r, ri_l, ri_r, 0});
        }
        // left subtree: preorder [pl+1, pl+1+left_size), inorder [il, idx)
        int lp_l = pl + 1, lp_r = pl + 1 + left_size;
        int li_l = il, li_r = idx;
        if (lp_l < lp_r) {
            st.push_back({false, lp_l, lp_r, li_l, li_r, 0});
        }
    }

    // print postorder
    for (int i = 0; i < n; i++) {
        cout << post[i] << (i+1<n ? ' ' : '\n');
    }
    return 0;
}
