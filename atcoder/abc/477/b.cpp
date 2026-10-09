#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Person {
    long long coord;
    int id;
};

int main() {
    // Optimize standard I/O operations for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    long long D;
    if (!(std::cin >> N >> D)) return 0;

    std::vector<Person> people(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> people[i].coord;
        people[i].id = i + 1; // 1-based indexing
    }

    // Sort people based on their coordinates
    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.coord < b.coord;
    });

    std::vector<int> standing_apart;

    for (int i = 0; i < N; ++i) {
        bool is_isolated = true;

        // Check distance to the left neighbor
        if (i > 0) {
            if (people[i].coord - people[i - 1].coord < D) {
                is_isolated = false;
            }
        }

        // Check distance to the right neighbor
        if (i < N - 1) {
            if (people[i + 1].coord - people[i].coord < D) {
                is_isolated = false;
            }
        }

        if (is_isolated) {
            standing_apart.push_back(people[i].id);
        }
    }

    // Sort the collected IDs in ascending order
    std::sort(standing_apart.begin(), standing_apart.end());

    // Print the result
    for (int id : standing_apart) {
        std::cout << id << "\n";
    }

    return 0;
}
