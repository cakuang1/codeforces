 
    #include <bits/stdc++.h>
    
    using namespace std;

    int n;
    
    vector<int> a(n); 

    
    int length = (int) sqrt(n + .0) + 1;
    vector<int> b(length);
    for (int i = 0 ; i < n; i ++ ) {
        b[i/len] += a[i];             
    }
    
     
    struct Query {
        int L ,R ,idx; 
    }

    int B; 
    vector>int> freq, a;
    long long current_ans = 0;
    vector<long long> ans; 
    
        
    bool cmp(const Query &p, const Query &q) {
        int block_p = p.L / B;
        int block_q = q.L / B;
        if (block_p != block_q)
            return block_p < block_q;
        // optional: alternate R order for better locality
        return (block_p & 1) ? (p.R > q.R) : (p.R < q.R);
    }
    int l ,r; 
    for (int i = l ;  i <= r; i ++) {
        // how to solve this and why does thsi wewti wewok 
        if (i % length ) {
        }
    }
    