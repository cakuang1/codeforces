#include <bits/stdc++.h>
using namespace std;

struct Person {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<Person> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i].x >> a[i].y >> a[i].z;
        }

        sort(a.begin(), a.end(), [](const Person& A, const Person& B) {
            if (A.x != B.x) return A.x > B.x;
            if (A.y != B.y) return A.y > B.y;
            return A.z > B.z;
        });

        vector<int> sufX(N), sufY(N), sufZ(N);

        sufX[N - 1] = a[N - 1].x;
        sufY[N - 1] = a[N - 1].y;
        sufZ[N - 1] = a[N - 1].z;

        for (int i = N - 2; i >= 0; --i) {
            sufX[i] = max(sufX[i + 1], a[i].x);
            sufY[i] = max(sufY[i + 1], a[i].y);
            sufZ[i] = max(sufZ[i + 1], a[i].z);
        }

        int minX = INT_MAX;
        int minY = INT_MAX;
        int minZ = INT_MAX;

        int ans = N;

        for (int i = 0; i < N - 1; ++i) {
            minX = min(minX, a[i].x);
            minY = min(minY, a[i].y);
            minZ = min(minZ, a[i].z);

            if (minX > sufX[i + 1] &&
                minY > sufY[i + 1] &&
                minZ > sufZ[i + 1]) {

                ans = i + 1;
                break;
            }
        }

        cout << ans << '\n';
    }

    return 0;
} 

// wer wrhwi