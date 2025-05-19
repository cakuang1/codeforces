#include <bits/stdc++.h>
using namespace std;

// Rotate an n×n grid of chars 90° clockwise in place
void rotateSquare(vector<string>& A) {
    int N = A.size();
    // transpose
    for (int i = 0; i < N; ++i)
        for (int j = i+1; j < N; ++j)
            swap(A[i][j], A[j][i]);
    // reverse each row
    for (int i = 0; i < N; ++i)
        reverse(A[i].begin(), A[i].end());
}

// Count how many cells differ between two n×n char‐grids
int diffCount(const vector<string>& A, const vector<string>& B) {
    int n = A.size(), cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j] != B[i][j]) ++cnt;
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> S(n), T(n);
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> T[i];
    }

    // try 0..3 rotations
    int best = diffCount(S, T);
    for (int r = 1; r <= 3; ++r) {
        rotateSquare(S);
        // cost = r rotations + flips for the current orientation
        best = min(best, r + diffCount(S, T));
    }

    cout << best << "\n";
    return 0;
}
