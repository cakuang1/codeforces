#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> requests(n); 
    // requests[i] = {c_i, p_i}
    for(int i=0;i<n;i++){
        cin >> requests[i].first >> requests[i].second;
    }

    // Keep original index so we can output it
    vector<int> origIndex(n);
    iota(origIndex.begin(), origIndex.end(), 0);

    // Sort requests by p_i descending (if tie, just by smaller c_i or by index)
    // We'll do a custom comparator
    sort(origIndex.begin(), origIndex.end(), [&](int a, int b){
        // primary key: requests[a].second > requests[b].second
        // secondary key (optional): requests[a].first < requests[b].first
        if(requests[a].second != requests[b].second)
            return requests[a].second > requests[b].second;
        return requests[a].first < requests[b].first; // tie-break
    });

    int k;
    cin >> k;
    vector<int> table(k);
    for(int j=0;j<k;j++){
        cin >> table[j];
    }
    // sort by increasing w
    // Keep original table indices in order to output them
    vector<int> tableIndex(k);
    iota(tableIndex.begin(), tableIndex.end(), 0);

    // Sort tables by ascending capacity
    sort(tableIndex.begin(), tableIndex.end(), [&](int a, int b){
        return table[a] < table[b];
    });

    // We'll store the final answer pairs: (requestOriginalIndex, tableOriginalIndex)
    vector<pair<int,int>> answer;
    long long totalProfit = 0;

    // We'll keep track of which tables are used
    vector<bool> used(k, false);

    // For each request in descending order of profit
    for(int idx: origIndex){
        int c = requests[idx].first; 
        long long p = requests[idx].second;
        // Find the smallest table that can seat c
        int chosen = -1; 
        // We'll do a simple linear scan of the sorted tables
        //   if you want to do it faster, you can do a binary search for the capacity
        //   but then you also need to find the next "unused" table, so a typical approach
        //   might be a balanced tree or a pointer that scans from left to right.
        for(int j=0;j<k;j++){
            int realTableIdx = tableIndex[j]; 
            if(!used[j] && table[realTableIdx] >= c){
                chosen = j;
                break;
            }
        }
        if(chosen != -1){
            used[chosen] = true;
            // chosen is an index in the sorted table array, so the "real table" is tableIndex[chosen]
            answer.push_back({idx, tableIndex[chosen]});
            totalProfit += p;
        }
    }

    // Output: number of accepted requests, total profit
    cout << answer.size() << " " << totalProfit << "\n";

    // The problem wants them in "any order" or typically "in the order we accepted them"
    // but it also says "requests are 1-based, tables 1-based" - so we add 1
    // and we should print "requestIndex, tableIndex" each line
    // The request index should be the 1-based index from input (that is idx+1).
    // The table index should be tableIndex[chosen]+1, also 1-based.
    for(auto &pr : answer){
        // pr.first = original request index
        // pr.second = original table index
        cout << (pr.first + 1) << " " << (pr.second + 1) << "\n";
    }
    return 0;
}
