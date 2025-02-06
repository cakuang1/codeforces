#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

const int Maxn = 105;
const int Maxd = 10;
const int Inf = 2000000007;

int n;
int F[Maxn][Maxd];
int P[Maxn][Maxd + 1];
int res = -Inf;

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < Maxd; j++)
			scanf("%d", &F[i][j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= Maxd; j++)
			scanf("%d", &P[i][j]);
	for (int i = 1; i < 1 << Maxd; i++) {
		int cand = 0;
		for (int j = 0; j < n; j++) {
			int sam = 0;
			for (int k = 0; k < Maxd; k++)
				sam += bool(i & 1 << k) && F[j][k];
			cand += P[j][sam];
		}
		res = max(res, cand);
	}
	printf("%d\n", res);
	return 0;
}