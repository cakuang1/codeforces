#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    
    // If the line contains only girls or only boys, no swaps are needed.
    if(s.find('M') == string::npos || s.find('F') == string::npos){
        cout << 0 << "\n";
        return 0;
    }
    
    // Remove initial girls: find the first index that is a boy.
    int firstBoy = 0;
    while(firstBoy < n && s[firstBoy] == 'F')
        firstBoy++;
    
    // Now, from position firstBoy onward, record the positions of all girls.
    // (We assume positions are 1-indexed.)
    vector<int> movingGirls; // x_i values
    for (int i = firstBoy; i < n; i++){
        if(s[i] == 'F'){
            // record its position (1-indexed)
            movingGirls.push_back(i + 1);
        }
    }
    
    // If there are no moving girls (all girls were at the very beginning), answer is 0.
    if(movingGirls.empty()){
        cout << 0 << "\n";
        return 0;
    }
    
    // In the final arrangement, the relative order of girls is preserved.
    // The moving girls will be placed at the very beginning of the line.
    // For these girls, let y_i be the final (target) position.
    // We can assume y_i = i (for i = 1,2,..., number of moving girls).
    // Let t_i be the time when the i-th moving girl is settled.
    // Each girl needs at least (x_i - y_i) seconds (since she moves one position per second),
    // but also she cannot finish before 1 second after the previous girl.
    
    int k = movingGirls.size();
    // t[0] for the first moving girl:
    int t_prev = movingGirls[0] - 1;  // since y_1 = 1
    // Process subsequent moving girls:
    for (int i = 1; i < k; i++){
        int need = movingGirls[i] - (i + 1);  // x_i - y_i, where y_i = i+1
        // She cannot finish before the previous girl finishes plus one second.
        int t_curr = max(need, t_prev + 1);
        t_prev = t_curr;
    }
    
    cout << t_prev << "\n";
    return 0;
}



