#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, double> memo;

double p_win_1_rec(int W, int B) {
    // Base cases
    if (W <= 0) return 0.0; // No white mice left, princess loses
    if (B <= 0) return 1.0; // No black mice left, princess wins

    // Memoization
    pair<int, int> args = make_pair(W, B);
    if (memo.find(args) != memo.end()) {
        return memo[args];
    }

    // Princess' turn
    double ret = W * 1.0 / (W + B); // Probability princess wins directly by drawing white
    double cont_prob = B * 1.0 / (W + B); // Probability of drawing a black mouse

    // Dragon's turn
    if (B > 1) {
        cont_prob *= (B - 1) * 1.0 / (W + B - 1); // Dragon draws black again
        double p_black = (B - 2 >= 0) ? p_win_1_rec(W, B - 3) * ((B - 2) * 1.0 / (W + B - 2)) : 0.0;
        double p_white = (W > 0) ? p_win_1_rec(W - 1, B - 2) * (W * 1.0 / (W + B - 2)) : 0.0;

        ret += cont_prob * (p_black + p_white);
    }

    // Store result in memoization table and return
    memo[args] = ret;
    return ret;
}

int main() {
    int W, B;
    cin >> W >> B;

    // Clear memoization table before each run
    memo.clear();

    // Compute the probability of the princess winning
    double result = p_win_1_rec(W, B);

    // Output the result with precision
    cout << fixed << setprecision(10) << result << "\n";

    return 0;
}