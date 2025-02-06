#include <bits/stdc++.h>
using namespace std;

struct State {
    int balance, lastWeight, step;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> weights;
    int m;

    // Input the weights available and the number of steps
    for (int i = 1; i <= 10; i++) {
        char c;
        cin >> c;
        if (c == '1') {
            weights.push_back(i);
        }
    }
    cin >> m;

    queue<State> q;
    map<tuple<int, int, int>, tuple<int, int, int>> parent; // For reconstructing the path
    set<tuple<int, int, int>> visited; // To avoid duplicate states

    q.push({0, 0, 1}); // Initial state: balance = 0, lastWeight = 0, step = 1
    visited.insert({0, 0, 1});

    while (!q.empty()) {
        auto [balance, lastWeight, step] = q.front();
        q.pop();

        if (step > m) {
            cout << "YES" << endl;
            // Reconstruct the sequence
            vector<int> sequence;
            tuple<int, int, int> current = {balance, lastWeight, step};
            while (get<2>(current) != 1) {
                sequence.push_back(get<1>(current));
                current = parent[current];
            }
            reverse(sequence.begin(), sequence.end());

            // Print the sequence
            for (int w : sequence) {
                cout << w << " ";
            }
            cout << endl;
            return 0;
        }

        for (int w : weights) {
            if (w == lastWeight) continue; // Cannot use the same weight consecutively

            int newBalance;
            if (step % 2 == 1) {
                // Add weight to the left pan
                newBalance = balance + w;
            } else {
                // Add weight to the right pan
                newBalance = balance - w;
            }

            // Ensure the new balance changes sign and is valid
            if (newBalance != 0 && abs(newBalance) <= 10 && (balance == 0 || (newBalance > 0) != (balance > 0))) {
                tuple<int, int, int> newState = {newBalance, w, step + 1};
                if (visited.find(newState) == visited.end()) {
                    visited.insert(newState);
                    parent[newState] = {balance, lastWeight, step};
                    q.push({newBalance, w, step + 1});
                }
            }
        }
    }

    // If no valid sequence  found
    cout << "NO" << endl;
    return 0;
}
