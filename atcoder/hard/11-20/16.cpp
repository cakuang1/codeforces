#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#define SIZE 10005

using namespace std;
typedef long long int ll;
typedef pair <int,int> P;

char str[SIZE];


int main()
{
	int n;
	scanf("%d",&n);
	int cnt=0;
	int a=0,b=0,ba=0;
	for(int i=0;i<n;i++)
	{
		scanf("%s",&str);
		int L=strlen(str);
		for(int j=0;j+1<L;j++)
		{
			if(str[j]=='A'&&str[j+1]=='B')
			{
				cnt++;
			}
		}
		if(str[0]=='B') b++;
		if(str[L-1]=='A') a++;
		if(str[0]=='B'&&str[L-1]=='A') ba++;
	}

 	cnt+=min(a,b);
	if(a==ba&&b==ba&&b>0) cnt--;
	printf("%d\n",cnt);
	return 0;
}
