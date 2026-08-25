#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;
using namespace atcoder;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++) cin >> p[i];
  
    fenwick_tree<int> fw(n);
    long long ans = 0, a;
  
    for(int i = 0; i < n; i++){
        a = fw.sum(p[i], n);
        ans += (a * (2LL * i - a + 1)) / 2;
        fw.add(p[i] - 1, 1);
    }
	
    cout << ans << endl;
    return 0;
}

// ww sdf wprsufs s wr
// werth nbusemrs sons wer

// actuviafetis hwirw

// truely ertru wetotu sfuwhi wer

// greedily turn wethese to ones 
// wgredily r so lsrhjis rhwiowr


/