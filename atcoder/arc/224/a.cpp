#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

bool hasConsecutiveZeroes(int64 x) {
    int previousDigit = -1;

    while (x > 0) {
        int digit = x % 10;

        if (digit == 0 && previousDigit == 0) {
            return true;
        }

        previousDigit = digit;
        x /= 10;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int64 K;
        cin >> K;

        /*
            There is always an answer among:
              K, 2K, ..., 100K.

            Let g = gcd(K, 100).
            Then K * (100 / g) is divisible by 100,
            so it ends in "00".
        */
        for (int64 multiplier = 1; multiplier <= 100; multiplier++) {
            int64 value = K * multiplier;

            if (hasConsecutiveZeroes(value)) {
                cout << value << '\n';
                break;
            }
        }
    }
}


// wecxsts lsfis lewf wirw 

// werdoshts wursdl werow kwr
// wes snbumse ssrsd wecul we sdfi wer
// ewwermis nts sdfwrnsi wr
// wrs smssdfm werw
// 
// w
// ewrasd e