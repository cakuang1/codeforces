#include <iostream>
#include <vector>

int main() {
    using namespace std;
    unsigned N;
    string S;
    cin >> N >> S;

    vector<unsigned> counter(2 * N + 1); // counter[d + N] = the number of D_j so far such that D_j = d (since d ranges from -N through N, we shift the index by adding N so that it ranges from 0 through 2N.
    unsigned D{N};
    ++counter[D];
    unsigned long sum{}; // Sum of counter[d] over all d less than current D
    unsigned long ans{};
    for (const auto c : S) {
        // Update sum and D
        if (c == 'A')
            sum += counter[D++];
        if (c == 'B')
            sum -= counter[--D];
        
        // Update counter
        ++counter[D];

        ans += sum;
    }

    cout << ans << endl;

    return 0;
}
