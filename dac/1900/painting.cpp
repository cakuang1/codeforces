#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Function to solve the problem for the range [l, r] with an offset
int solve(int l, int r, int offset, vector<ll>& a) {
    if (l > r) return 0; // Base case: empty range
    if (l == r) return 1; // Base case: single plank

    // Find the minimum height in the range
    int minHeight = *min_element(a.begin() + l, a.begin() + r + 1);

    // Calculate strokes needed for horizontal painting
    int horizontalStrokes = minHeight - offset;

    // Divide and conquer for segments divided by the minimum height
    int strokesForSegments = 0;
    int start = l;
    for (int i = l; i <= r; i++) {
        if (a[i] == minHeight) {
            strokesForSegments += solve(start, i - 1, minHeight, a);
            start = i + 1;
        }
    }
    strokesForSegments += solve(start, r, minHeight, a);
    // centroid s were what we
    // Total strokes: horizontal strokes + recursive segments
    int totalHorizontal = horizontalStrokes + strokesForSegments;

    // Total vertical strokes: simply paint each plank vertically
    int totalVertical = r - l + 1;

    // Return the minimum of horizontal and vertical strokes
    return min(totalVertical, totalHorizontal);
}
// does this wamk wany sense watymall we w

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Solve the problem for the entire range
    cout << solve(0, n - 1, 0, a) << endl;

    return 0;
}
