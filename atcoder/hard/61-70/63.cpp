#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define MOD @
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;

int N, K, D[10];
bool H[10];

bool hate(int V)
{
	while (V) {
		if (H[V % 10]) return false;
		V /= 10;
	}
	return true;
}

int main()
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i < 10; ++i) H[i] = false;
	for (int i = 0; i < K; ++i) {
		scanf("%d", D + i);
		H[D[i]] = true;
	}
	for (;;) {
		if (hate(N)) {
			printf("%d\n", N);
			break;
		}
		++N;
	}
	return 0;
}
