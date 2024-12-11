#include <bits/stdc++.h>
using namespace std;

const int N = 200043;

int p[2][N];       // Parent pointers for 0-graph and 1-graph
int siz[2][N];     // Sizes of connected components for 0-graph and 1-graph

// Find function with path compression
int get(int x, int c) {
    if (p[c][x] == x)
        return x;
    return p[c][x] = get(p[c][x], c);
}

// Union function with union by size
void merge(int x, int y, int c) {
    x = get(x, c);
    y = get(y, c);
    if (x == y)
        return; // Already in the same component
    if (siz[c][x] < siz[c][y])
        swap(x, y);
    p[c][y] = x;
    siz[c][x] += siz[c][y];
}

int main() {
    int n;
    scanf("%d", &n);
    
    // Initialize DSUs
    for (int i = 0; i < n; i++) {
        p[0][i] = p[1][i] = i;
        siz[0][i] = siz[1][i] = 1;
    }
    
    // Read edges and merge components
    for (int i = 0; i < n - 1; i++) {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        --x; --y; // Convert to 0-based indexing
        merge(x, y, c); // Merge in the appropriate DSU
    }
    
    long long ans = 0;
    
    // Calculate pairs within 0-components and 1-components
    for (int i = 0; i < n; i++) {
        if (p[0][i] == i) {
            long long s = siz[0][i];
            ans += s * (s - 1); // Pairs in 0-component
        }
        if (p[1][i] == i) {
            long long s = siz[1][i];
            ans += s * (s - 1); // Pairs in 1-component
        }
    }
    // how to see this  
    
    // why does this even make weense 
    
    // Calculate mixed pairs
    for (int i = 0; i < n; i++) {
        long long s0 = siz[0][get(i, 0)];
        long long s1 = siz[1][get(i, 1)];
        ans += (s0 - 1) * (s1 - 1);
    }
    
    printf("%lld\n", ans);
    return 0;
}
