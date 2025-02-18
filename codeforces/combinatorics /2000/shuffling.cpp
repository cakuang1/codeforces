#include <bits/stdc++.h>     

using namespace std;

const int MOD = 998244353;

int add(int x, int y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}

int main()
{
    int n;
    cin >> n;
    int k;
    cin >> k;
    string s;
    cin >> s;
    vector<int> p(n + 1);
    for(int i = 0; i < n; i++) p[i + 1] = p[i] + (s[i] - '0');
    vector<vector<int>> C(n + 1);
    for(int i = 0; i <= n; i++)
    {
        C[i].resize(i + 1);
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++)
            C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
    }
    int ans = 1;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
        {
            int cnt = j + 1 - i;
            int cnt1 = p[j + 1] - p[i];
            if(cnt1 > k || p[n] < k) continue;
            cnt -= 2;
            if(s[i] == '0') cnt1--;
            if(s[j] == '0') cnt1--;
            if(cnt1 <= cnt && cnt1 >= 0 && cnt >= 0)
                ans = add(ans, C[cnt][cnt1]);
        }
    cout << ans << endl;
}



