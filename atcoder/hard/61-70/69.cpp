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

int N; i64 A[101010];
i64 D[101010];

i64 hoge()
{
	int top = 0, end = N - 2;
	int a = 1;
	i64 ret = 0;
	while (top <= end) {
		if (a % 2 == 0) {
			ret += a * D[top++];
		} else {
			ret += a * D[end--];
		}
		++a;
	}
	return ret;
}
int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%lld", A + i);

	sort(A, A + N);

	for (int i = 0; i < N - 1; ++i) D[i] = A[i + 1] - A[i];

	i64 ret = 0;
	int a = 1;
	int top = 0, end = N - 2;
	for (;;) {
		if (end - top == 0) {
			ret += D[top] * (N - 1);
			break;
		} else if (end - top == 1) {
			ret += (D[end] + D[top]) * (N - 2);
			ret += max(D[end], D[top]);
			break;
		} else {
			ret += (D[end] + D[top]) * a * 2;
			++a;
			--end;
			++top;
		}
	}
	printf("%lld\n", ret);

	return 0;
}