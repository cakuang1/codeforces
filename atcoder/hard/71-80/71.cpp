#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <tuple>
#include <iterator>

using namespace std;

int arr[200010];

int main()
{
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);

    int n, i;
    scanf("%d", &n);
    for(i = 1; i <= n; i++)
        scanf("%d", &arr[i]);

    for(i = 1; i <= n; i++)
        arr[i] -= i;

    sort(arr + 1, arr + n + 1);

    int b = arr[n / 2 + 1];

    long long res = 0;
    for(i = 1; i <= n; i++)
        res += abs(arr[i] - b);

    printf("%lld\n", res);
    return 0;
}