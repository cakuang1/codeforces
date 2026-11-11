
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> arr(n);

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;

        arr[i].resize(c);

        for (int j = 0; j < c; j++) {
            cin >> arr[i][j];
        }
    }

    int x;
    cin >> x;

    int mn = INT_MAX;
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int v : arr[i]) {
            if (v == x) {
                found = true;
                break;
            }
        }

        if (!found) continue;

        int c = arr[i].size();

        if (c < mn) {
            mn = c;
            ans.clear();
            ans.push_back(i + 1);
        } else if (c == mn) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << '\n';

    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
