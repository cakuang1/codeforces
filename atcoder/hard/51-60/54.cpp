#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y, a, b, c;
    cin >> x >> y >> a >> b >> c; 
    
    vector<int> red(a);
    vector<int> green(b);
    vector<int> white(c);

    // Read red apples
    for (int i = 0; i < a; i++) {
        cin >> red[i];
    }
    // Read green apples
    for (int i = 0; i < b; i++) {
        cin >> green[i];
    }
    // Read colorless apples
    for (int i = 0; i < c; i++) {
        cin >> white[i];
    }

    // Sort red and green apples in descending order (greedy selection)
    sort(red.begin(), red.end(), greater<int>());
    sort(green.begin(), green.end(), greater<int>());
    sort(white.begin(), white.end(), greater<int>());  // Sort white apples in descending order

    // Min-heap (to track the lowest deliciousness apples in our selection)
    priority_queue<int, vector<int>, greater<int>> q;
    ll sum = 0;

    // Pick the `x` most delicious red apples
    for (int i = 0; i < x; i++) {
        sum += red[i];
        q.push(red[i]);
    }

    // Pick the `y` most delicious green apples
    for (int i = 0; i < y; i++) {
        sum += green[i];
        q.push(green[i]);
    }

    // Try replacing the least delicious apples with colorless apples (if better)
    for (int i = 0; i < c; i++) {
        if (!q.empty() && white[i] > q.top()) {  // Only replace if better
            sum += white[i] - q.top();
            q.pop();
            q.push(white[i]);  // Push new replaced value into heap
        } else {
            break;  // No further replacements needed
        }
    }

    cout << sum << endl;
    return 0;
}
