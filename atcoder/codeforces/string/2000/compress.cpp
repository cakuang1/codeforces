#include<cstdio>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<cstring>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<numeric>
#include<cctype>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<list>
#include<set>
#include<map>
using namespace std;
 
const int N = 10000002;
int nxt[N];
char S[N], T[N],str1[N],str2[N];
int slen, tlen;
 
void getNext()
{
    int j, k;
    j = 0;
    k = -1;
    nxt[0] = -1;
    while(j < tlen)
        if(k == -1 || T[j] == T[k])
        {
            nxt[++j] = ++k;
            if (T[j] != T[k]) //KMP优化,加速得到next数组
                nxt[j] = k;
        }
        else
            k = nxt[k];
}
/*
返回模式串T在主串S中首次出现的位置
返回的位置是从0开始的
*/
int KMP_Index()
{
    int i = max(slen-tlen,0), j = 0;
    getNext();
    while(i < slen && j < tlen)
    {
        if(j == -1 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = nxt[j];
    }
    return j;//T串前缀在主串S可以匹配的最远的可匹配的位置
}


int main()
{
 
    int n;
    scanf("%d",&n);
    scanf("%s",S);
	slen=strlen(S);
    for(int i=1; i<n; i++)
    {
        scanf("%s",T);
        tlen = strlen(T);
        int pos=KMP_Index();
        //printf(" pos =  %d  \n",pos);
        //cout<<pos<<endl;
		for(int j=pos;j<tlen;j++)
		{
			S[slen]=T[j];
			slen++;
		}
    }
    printf("%s",S);

return 0;
}