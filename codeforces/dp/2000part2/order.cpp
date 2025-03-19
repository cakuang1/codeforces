#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Maximum number of positions: up to 24 objects + 1 handbag = 25.
const int MAX_OBJ = 25;
// Maximum number of states in the DP (if N == 24, then 1<<24 states)
const int MAX_STATES = 1 << 24;

int N; // number of objects (will be <= 24)
pair<int, int> obj[MAX_OBJ];  // indices 0..N-1 for objects, index N for the handbag
int Dist[MAX_OBJ][MAX_OBJ];   // precomputed squared distances

// We'll allocate DP arrays for up to 1<<24 states.
int dp[MAX_STATES];
int fromState[MAX_STATES];    
pair<int, int> tripState[MAX_STATES]; // for each state, stores the objects picked: second = -1 if only one

// Compute squared Euclidean distance between points at indices i and j.
int calcDist(int i, int j) {
    int dx = obj[i].first - obj[j].first;
    int dy = obj[i].second - obj[j].second;
    return dx * dx + dy * dy;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Input handbag location.
    int hx, hy;
    cin >> hx >> hy;
    
    // Input number of objects.
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> obj[i].first >> obj[i].second;
    }
    // Use index N to represent the handbag.
    obj[N] = {hx, hy};
    
    // Precompute distances between every pair (including handbag-object).
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++){
            Dist[i][j] = calcDist(i, j);
        }
    }
    
    int fullMask = (1 << N) - 1;
    for (int mask = 0; mask <= fullMask; mask++){
        dp[mask] = INF;
    }
    dp[0] = 0; // base state: no object picked
    
    // DP over bitmasks.
    for (int mask = 0; mask <= fullMask; mask++){
        if (dp[mask] == INF)
            continue;
        
        // Only consider the first uncollected object.
        int first = -1;
        for (int i = 0; i < N; i++){
            if (!(mask & (1 << i))) {
                first = i;
                break;
            }
        }
        if (first == -1)
            continue; // all objects collected
        
        // Option 1: Pick only the first object (trip: H -> first -> H).
        int newMask = mask | (1 << first);
        int cost = 2 * Dist[N][first];
        if (dp[newMask] > dp[mask] + cost) {
            dp[newMask] = dp[mask] + cost;
            fromState[newMask] = mask;
            tripState[newMask] = {first, -1}; // only one object picked
        }
        
        // Option 2: Pair 'first' with another uncollected object j (j > first).
        for (int j = first + 1; j < N; j++){
            if (!(mask & (1 << j))) {
                int newMaskPair = mask | (1 << first) | (1 << j);
                int costPair = Dist[N][first] + Dist[first][j] + Dist[j][N]; // trip: H -> first -> j -> H
                if (dp[newMaskPair] > dp[mask] + costPair) {
                    dp[newMaskPair] = dp[mask] + costPair;
                    fromState[newMaskPair] = mask;
                    tripState[newMaskPair] = {first, j};
                }
            }
        }
    }
    
    // Output the minimum total cost.
    cout << dp[fullMask] << "\n";
    
    // Reconstruct the trips by backtracking the DP.
    vector<vector<int>> trips;
    int mask = fullMask;
    while (mask) {
        auto [a, b] = tripState[mask];
        // Build the current trip; each trip starts and ends at the handbag (index N, printed as 0).
        vector<int> currentTrip = {N, a};
        if (b != -1)
            currentTrip.push_back(b);
        currentTrip.push_back(N);
        trips.push_back(currentTrip);
        mask = fromState[mask];
    }
    
    // The trips are recovered in reverse order; reverse them.
    reverse(trips.begin(), trips.end());
    
    // Merge the trips into a single sequence.
    // For the first trip, output the whole trip.
    // For subsequent trips, skip the first element (handbag) to avoid duplicates.
    vector<int> route;
    if (!trips.empty()){
        for (int id : trips[0])
            route.push_back(id == N ? 0 : id + 1);
        for (size_t i = 1; i < trips.size(); i++){
            for (size_t j = 1; j < trips[i].size(); j++)
                route.push_back(trips[i][j] == N ? 0 : trips[i][j] + 1);
        }
    }
    
    // Print the merged route.
    for (int x : route)
        cout << x << " ";
    cout << "\n";
    
    return 0;
}
