#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// Build the permutation describing one full game's reshuffling
vector<int> build_perm(int N) {
    vector<int> perm;
    perm.reserve(5 * N);
    // From player N down to 1 (collect right-to-left)
    for (int player = N; player >= 1; --player) {
        // Cards dealt to this player (0-based indices in deck)
        vector<int> dealt = {
            2 * (player - 1),
            2 * (player - 1) + 1,
            2 * N + 2 * (player - 1),
            2 * N + 2 * (player - 1) + 1,
            4 * N + (player - 1)
        };
        // Collect in reverse dealing order
        reverse(dealt.begin(), dealt.end());
        for (int idx : dealt)
            perm.push_back(idx);
    }
    return perm;
}

// Precompute which player owns each position in the deck
vector<int> build_owner_map(int N) {
    vector<int> owner(5 * N);
    for (int player = 0; player < N; ++player) {
        owner[2 * player] = player;
        owner[2 * player + 1] = player;
        owner[2 * N + 2 * player] = player;
        owner[2 * N + 2 * player + 1] = player;
        owner[4 * N + player] = player;
    }
    return owner;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int N;
        if (!(cin >> N)) return 0;
        if (N == 0) break;

        vector<int> deck(5 * N);
        for (int i = 0; i < 5 * N; ++i) cin >> deck[i];

        // Build permutation P (one game transition)
        vector<int> perm = build_perm(N);
        vector<int> owner = build_owner_map(N);

        // Find initial positions of cards 1..5
        vector<int> pos(5);
        for (int i = 0; i < 5 * N; ++i) {
            if (deck[i] <= 5)
                pos[deck[i] - 1] = i;
        }

        // Cycle detection: map from tuple(pos1..pos5) -> game index
        map<array<int, 5>, long long> seen;
        array<int, 5> state;
        for (int i = 0; i < 5; ++i) state[i] = pos[i];

        long long game = 0;
        while (true) {
            game++;

            // Determine which player each card 1..5 belongs to
            int first_owner = owner[state[0]];
            bool all_same = true;
            for (int i = 1; i < 5; ++i) {
                if (owner[state[i]] != first_owner) {
                    all_same = false;
                    break;
                }
            }

            if (all_same) {
                cout << "Player " << (first_owner + 1)
                     << " wins game number " << game << ".\n";
                break;
            }

            // Check for repetition (cycle)
            if (seen.count(state)) {
                cout << "Neverending game.\n";
                break;
            }
            seen[state] = game;

            // Apply permutation once (simulate one game)
            for (int i = 0; i < 5; ++i)
                state[i] = perm[state[i]];
        }
    }
    return 0;
}

//w