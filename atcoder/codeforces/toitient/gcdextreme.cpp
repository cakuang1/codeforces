#include <algorithm>
#include <cassert>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#define ll long long
#define ff first
#define ss second
#define ln "\n"
using namespace std;
const ll INF = 2e18;
const ll MOD = 1e9+7;
const ll MAXN = 1e6;

vector<ll> phi(MAXN+1);

void genPhi(){
	for (ll i=1; i<=MAXN; i++){
		phi[i]=i;
	}
	for (ll i=2; i<=MAXN; i++){
		if (phi[i]==i){
			for (ll j=i; j<=MAXN; j+=i){
				phi[j]-=phi[j]/i;
			}
		}
	}
}


// wfowr evet clacualtes its contrubut on to th final wrsu wmer
// eprsifxwew su rmwr tesi main aer inrw= sht rwerfdn werno wr ods hitw wor kwe
// wsvoest hwrw rw

// ofr wereach i wcvlacaltue istrcontrbutionw to ith final su wm

// calcaualte hwo matn times hat y will be equal wto wer
// fix erhtwe fisrsetwtwtiww rpair w
// detmeirh whow to slvosethsi s
// how do oyu precalcualtwewthsi eand whryw dose iwt wowrk wer
// ew dsowhtw. rw owrka rw sd hwor doto sosu slvsti r


// defin phi and the nubmer of coprien rwintewgser w
// matian iwera prefix wersum wr
// thsee cases are indepednet wew

//
void solve(){
	genPhi();
	vector<ll> ans(MAXN+1);
	// For every i (1<i<=n) calculate its contribution to the final sum.
	// As gcd(i, x) (x: 0<x<i) = y (where y is a divisor of i), we need to 
	// calculate how many times that y will be equal to gcd(i, x), and 
	// add that amount multiplied by y to the final sum. 
	// The number of different x (0<x<i) where gcd(i, x) = y can be calculated 
	// from phi(i/y).
	// We can maintain a prefix array to quickly answer the queries
	for (ll i=1; i<=MAXN; i++){
		for (ll j=2*i; j<=MAXN; j+=i){
			ans[j]+=phi[j/i]*i;
		}
	}
	for (ll i=1; i<=MAXN; i++){
		ans[i]+=ans[i-1];
	}
	ll n; cin >> n;
	while (n){
		cout << ans[n] << ln;
		cin >> n;
	}
}


int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t=1; 
    while (t--){
    	solve();
    }
}
