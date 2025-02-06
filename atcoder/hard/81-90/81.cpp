#include <bits/stdc++.h>
using namespace std;

long long A[100005];

int main()
{
    int N;
    long long x;
    cin >> N >> x;

    for(int i=1; i<=N; i++)
        cin >> A[i];

    long long ans = 0;

    for(int i=1; i<=N; i++)
    {
        if(A[i]+A[i-1]>x)
        {
            ans += ((A[i]+A[i-1])-x);
            A[i] -= ((A[i]+A[i-1])-x);
        }
    }

    cout << ans << endl;

    return 0;
}
