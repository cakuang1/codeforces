    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin >> n;
        vector<int> a(n);
        
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> b = a;

        auto getSubsetSums = [](vector<int>& arr) -> unordered_set<long long> {
            int size = arr.size();
            unordered_set<long long> sums;
            for (int mask = 1; mask < (1 << size); mask++) {
                long long sum = 0;
                for (int i = 0; i < size; i++) {
                    if (mask & (1 << i)) sum += arr[i];
                }
                sums.insert(sum);
            }
            return sums;
        };

        unordered_set<long long> originalSums = getSubsetSums(a);

        do {
            if (getSubsetSums(b) != originalSums) {
                for (int x : b) cout << x << " ";
                cout << endl;
                return 0;
            }
        } while (next_permutation(b.begin(), b.end()));

        cout << "-1\n";
        return 0;
    }
