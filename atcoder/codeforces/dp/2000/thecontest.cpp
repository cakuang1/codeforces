#include <bits/stdc++.h>

using namespace std;

int main() 
{
	int k1, k2, k3;
	scanf("%d %d %d", &k1, &k2, &k3);
	int n = k1 + k2 + k3;
	vector<int> a(n);
	for(int i = 0; i < k1; i++)
	{
		int x;
		scanf("%d", &x);
		a[x - 1] = 0;
	}
	for(int i = 0; i < k2; i++)
	{
		int x;
		scanf("%d", &x);
		a[x - 1] = 1;
	}
	for(int i = 0; i < k3; i++)
	{
		int x;
		scanf("%d", &x);
		a[x - 1] = 2;
	}
	
	int ans = 0;
	int bestp = 0;
	for(int i = 0; i < n; i++)
		if(a[i] != 2)
			ans++;
	vector<int> cntl(3);
	vector<int> cntr(3);
	for(int i = 0; i < n; i++)
		cntr[a[i]]++;
	for(int i = 0; i < n; i++)
	{
		cntl[a[i]]++;
		cntr[a[i]]--;
		bestp = max(bestp, cntl[0] - cntl[1]);
		int curans = cntr[0] + cntr[1] + cntl[2] + cntl[0] - bestp;
		ans = min(ans, curans);
	}
    // does htsi 
	cout << ans << endl; 
}                    	
