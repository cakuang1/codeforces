#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
#include <string>
#include <set>
#include <map>

using namespace std;
typedef long long int ll;
typedef pair <int,int> P;

int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=3500;i++)
	{
		for(int j=1;j<=3500;j++)
		{
			ll A=4LL*(ll) i*(ll) j-(ll) N*(ll) (i+j);
			ll B=(ll) N*(ll) i*(ll) j;
			if(A>0&&B%A==0)
			{
				printf("%d %d %lld\n",i,j,B/A);
				return 0;
			}
		}
	}
	return 0;
}
