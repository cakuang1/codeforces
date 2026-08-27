#include <bits/stdc++.h>
using namespace std;

struct Person {
    long long s, t;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Person> a(N);

    for (int i = 0; i < N; ++i) {
        cin >> a[i].s >> a[i].t;
        a[i].id = i + 1;
    }

    // Check whether the order of S and T is consistent.
    vector<Person> sorted = a;

    sort(sorted.begin(), sorted.end(),
         [](const Person& x, const Person& y) {
             return x.s < y.s;
         });

    for (int i = 0; i + 1 < N; ++i) {
        if (sorted[i].t > sorted[i + 1].t) {
            cout << "No\n";
            return 0;
        }
    }

    vector<Person> rightMove;
    vector<Person> leftMove;

    for (auto &p : a) {
        if (p.s < p.t)
            rightMove.push_back(p);
        else
            leftMove.push_back(p);
    }

    // Right movers: rightmost first.
    sort(rightMove.begin(), rightMove.end(),
         [](const Person& x, const Person& y) {
             return x.s > y.s;
         });

    // Left movers: leftmost first.
    sort(leftMove.begin(), leftMove.end(),
         [](const Person& x, const Person& y) {
             return x.s < y.s;
         });

    cout << "Yes\n";

    bool first = true;

    for (auto &p : rightMove) {
        if (!first) cout << ' ';
        first = false;
        cout << p.id;
    }

    for (auto &p : leftMove) {
        if (!first) cout << ' ';
        first = false;
        cout << p.id;
    }

    cout << '\n';
}