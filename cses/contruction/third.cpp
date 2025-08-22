#include <bits/stdc++.h>
using namespace std;

// Sieve primes up to maxN
vector<int> sieve(int maxN) {
    vector<bool> isP(maxN+1,true);
    isP[0]=isP[1]=false;
    for(int i=2;i*i<=maxN;i++) if(isP[i])
        for(int j=i*i;j<=maxN;j+=i) isP[j]=false;
    vector<int> P;
    for(int i=2;i<=maxN;i++) if(isP[i]) P.push_back(i);
    return P;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    // Generate all primes up to 2n
    auto primes = sieve(2*n + 5);

    vector<int> a(n+1), b(n+1, 0);
    for(int i=1;i<=n;i++) a[i]=i;

    // Partition
    vector<int> odds, evens;
    odds.reserve((n+1)/2);
    evens.reserve(n/2);
    for(int i=1;i<=n;i++){
        ((i&1)? odds: evens).push_back(i);
    }

    // If n odd: self‐pair 1
    unordered_set<int> usedE;
    if(n&1){
        b[1]=1;
        usedE.insert(1);
        // remove '1' from odds
        odds.erase(find(odds.begin(), odds.end(), 1));
    }

    // Match each odd to an even
    int pi = 0, P = primes.size();
    for(int o : odds){
        // advance pi until primes[pi] >= o+2
        while(pi<P && primes[pi] < o+2) pi++;
        // find a prime that yields an unused even e in [2..n]
        while(pi<P){
            int p = primes[pi];
            int e = p - o;
            if(e>=1 && e<=n && !(usedE.count(e))){
                b[o]=e;
                b[e]=o;
                usedE.insert(e);
                break;
            }
            pi++;
        }
    }

    // Check we filled all
    for(int i=1;i<=n;i++){
        if(b[i]==0){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }

    // Output
    for(int i=1;i<=n;i++){
        cout<<a[i]<<(i==n?'\n':' ');
    }
    for(int i=1;i<=n;i++){
        cout<<b[i]<<(i==n?'\n':' ');
    }
    return 0;
}
