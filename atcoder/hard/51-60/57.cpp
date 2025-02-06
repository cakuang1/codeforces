#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <cmath>
#define SIZE 200005

using namespace std;
typedef long long int ll;
typedef pair <int,int> P;

map <ll,int> mp;

int main()
{
	int n;
	scanf("%d",&n);
	ll ret=0,sum=0;
	mp[0]++;
	for(int i=0;i<n;i++)
	{
		ll a;
		scanf("%lld",&a);
		sum+=a;
		ret+=mp[sum];
		mp[sum]++;
	}
	printf("%lld\n",ret);
	return 0;
}
