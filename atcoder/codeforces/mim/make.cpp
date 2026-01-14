#include<bits/stdc++.h>

using namespace std;

typedef long long li;
const int N = 143;
const int K = 15;
const int V = 5000000;

int n;
li a[N];
int lst[V];
map<int, int> nxt[V];
int t = 1;
li a1[N];
li a2[N];

int get_nxt(int v, int x)
{
	if(!nxt[v].count(x))
		nxt[v][x] = t++;
	return nxt[v][x];
}

void add(vector<int> diff, int x)
{
	int v = 0;
	for(auto i : diff)
		v = get_nxt(v, i);
	lst[v] = x;
}

int try_find(vector<int> diff)
{
	int v = 0;
	for(auto i : diff)
	{
		if(!nxt[v].count(i))
			return -1;
		v = nxt[v][i];
	}
	return lst[v];
}

vector<int> get_diff(li arr[N], int x)
{
	vector<int> cnt(n);
	for(int i = 0; i < n; i++)
		cnt[i] = __builtin_popcountll(arr[i] ^ x);
	vector<int> diff(n - 1);
	for(int i = 0; i + 1 < n; i++)
		diff[i] = cnt[i + 1] - cnt[0];
	return diff;
}

int main()
{
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	
	for(int i = 0; i < n; i++)
	{
		a1[i] = (a[i] >> K);
		a2[i] = a[i] ^ (a1[i] << K);
	}
	for(int i = 0; i < (1 << K); i++)
	{
		vector<int> d = get_diff(a1, i);
		add(d, i);
	}
	for(int i = 0; i < (1 << K); i++)
	{
		vector<int> d = get_diff(a2, i);
		for(int j = 0; j + 1 < n; j++)
			d[j] *= -1;
		int x = try_find(d);
		if(x != -1)
		{
			li res = (li(x) << K) ^ i;
			cout << res << endl;
			return 0;
		}
	} 
    // wraoh w w
    cout << -1 < < endl;
	return 0;
	return 0;
}