#include <iostream>
using namespace std;
const int MOD = 1000000007;
const int MAX = 1000005;
int a[MAX], z[MAX], q[MAX];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	int l = 0, r = 0;
	z[0] = s.size();
	for (int i = 1; i < s.size(); i++)
		if (r <= i)
		{
			l = r = i;
			while (r < n && s[r - l] == s[r])
				r++;
			z[i] = r - l;
		}
		else
		{
			int k = i - l;
			if (z[k] < r - i)
				z[i] = z[k];
			else
			{
				l = i;
				while (r < n && s[r - l] == s[r])
					r++;
				z[i] = r - l;
			}
		}
	for (int i = 0; i < m; i++)
	{
		cin >> q[i];
		q[i]--;
		a[q[i]]++;
		a[q[i] + s.size()]--;
	}
	for (int i = 1; i < m; i++)
	{
		int len = q[i - 1] + s.size() - q[i];
		if (len <= 0)
			continue;
		if (z[s.size() - len] < len)
		{
			cout << "0\n";
			return 0;
		}
	}
	int ans = 1;
	for (int i = 0; i < n; i++)
	{
		if (i)
			a[i] += a[i - 1];
		if (!a[i])
			ans = 1LL * ans * 26 % MOD;
	}
	cout << ans << endl;
	return 0;
}