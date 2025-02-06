#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int mod = 998244353;

int main()
{
	string s, t;
	
	cin >> s >> t;
	int n = s.size();
	int m = t.size();
	
	vector<vector<int> > f(n + 1, vector<int>(m + 1));
	
	f[n][0] = 1;
	
	for (int i = n - 1; i >= 1; --i)
	{
		for (int j = 0; j <= m; ++j)
		{
			if (j == 0)
			{
				if (i >= m) f[i][0] = n - i + 1;
				else if (s[i] == t[i]) f[i][0] = f[i + 1][0];
			}
			else if (j == m)
			{
				f[i][m] = 2 * f[i + 1][m] % mod;
				if (s[i] == t[m - 1]) f[i][m] = (f[i][m] + f[i + 1][m - 1]) % mod;
			}
			else
			{
				if (i + j >= m || s[i] == t[i + j]) f[i][j] = f[i + 1][j];
				if (s[i] == t[j - 1]) f[i][j] = (f[i][j] + f[i + 1][j - 1]) % mod;
			}
		}
	}
	
	int ans = f[1][m];
	for (int i = 0; i < m; ++i) if (t[i] == s[0]) ans = (ans + f[1][i]) % mod;
	ans = ans * 2 % mod;
	
	cout << ans;
	
	return 0;
}