#include <iostream>
using namespace std;

int main() {
    int N, R; // Number of contests and initial rating
    cin >> N >> R;
    
    for (int i = 0; i < N; i++) {
        int division, score;
        cin >> division >> score;

        // Update rating based on division and current rating
        if (division == 1 && R >= 1600 && R <= 2799) {
            R += score;
        } else if (division == 2 && R >= 1200 && R <= 2399) {
            R += score;
        }
    }

    // Output the final rating
    cout << R << endl;
    return 0;
}

