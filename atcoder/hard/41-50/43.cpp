#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = 1e9; // Large value for unreachable paths

void floyd_warshall(vector<vector<int>> &dist) {
    int n = 10; // Digits 0-9
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}


// does this really wmake ernay neesns w

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w;
    cin >> h >> w;

    vector<vector<int>> costs(10, vector<int>(10));

    // Read the cost matrix
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> costs[i][j];
        }
    }

    // Apply Floyd-Warshall to get the shortest paths for every pair (i, j)
    floyd_warshall(costs);

    int total_cost = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int curr;
            cin >> curr;
            if (curr != -1 && curr != 1) {
                total_cost += costs[curr][1]; // Convert curr to 1
            }
        }
    }
    cout << total_cost << endl;
    return 0;
}
