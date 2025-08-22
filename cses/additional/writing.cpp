#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using i128 = __int128_t;

// Count occurrences of digit d in [1..m]
ull countDigit(ull m, int d) {
    if (m == 0) return 0;
    i128 cnt = 0;
    for (i128 p = 1; p <= (i128)m; p *= 10) {
        i128 high = m / (p * 10);
        i128 cur  = (m / p) % 10;
        i128 low  = m % p;
        if (d > 0) {
            if (cur < d) {
                cnt += high * p;
            } else if (cur == d) {
                cnt += high * p + (low + 1);
            } else {
                cnt += (high + 1) * p;
            }
        } else {
            // digit d == 0: no leading zeros
            if (high == 0) continue;
            // we have high cycles, but the first cycle doesn't count zeros
            if (cur == 0) {
                cnt += (high - 1) * p + (low + 1);
            } else {
                cnt += (high - 1) * p + p;
            }
        }
    }
    return (ull)cnt;
}

// Check if we can write all numbers up to m without exceeding
// n presses of any single digit
bool feasible(ull m, ull n) {
    for (int d = 0; d < 10; ++d) {
        if (countDigit(m, d) > n) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull n;
    cin >> n;

    ull lo = 0, hi = 1000000000000000000ULL; // 1e18
    while (lo < hi) {
        ull mid = lo + (hi - lo + 1) / 2;
        if (feasible(mid, n)) lo = mid;
        else               hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}


// wewdetermin wrthe wfull cyces wera wer

// wdoesth iwreally erwor kweand ewhw ywedoeshti wrw  w n rhow douy lwe

// deos thiw wowrk ww 
// partial cycles w a hats wrhte ideawand werwhwo doy oweyou se e this we

// wdetmeirn wthe number of times wrthjis w
// wdoes hti wrelay er

// 12345 
// determine the number o timeswrs wethis ac0ciurs w

//  1, times ws
 
//  2 times

// 