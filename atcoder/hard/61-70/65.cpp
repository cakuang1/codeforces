        #include <iostream>
        #include <vector>
        #include <unordered_map>
        #include <set>

        using namespace std;

        int main() {
            ios::sync_with_stdio(false);
            cin.tie(NULL);

            int n; 
            cin >> n;
            
            unordered_map<int, int> freq;  // Store frequency of each card
            set<int> unique_cards;         // Store distinct card values

            for (int i = 0; i < n; i++) {
                int s; 
                cin >> s;
                freq[s]++;  
                unique_cards.insert(s);
            }

            int k = unique_cards.size();  // Number of distinct values

            // If k is even, we must remove one single-occurrence card
            if (k % 2 == 0) {
                cout << k - 1 << endl;
            } else {
                cout << k << endl;
            }

            return 0;
        }
