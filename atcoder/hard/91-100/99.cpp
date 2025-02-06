#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define SIZE 100005

using namespace std;
typedef long long int ll;

int A[SIZE];

int main()
{
	int n;
	scanf("%d",&n);
	ll ret=0;
	bool up=false;
	for(int i=0;i<n;i++)
	{
		int a;
		scanf("%d",&a);
		if(up&&a>0)
		{
			a--;
			ret++;
		}
		ret+=a/2;
		up=a%2==0?false:true;
	}
	printf("%lld\n",ret);
	return 0;
}
