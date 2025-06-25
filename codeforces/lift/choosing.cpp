#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
#define SIZE 131072
vector<int>pat[100000];
vector<int>ko[100000];
int par[19][100000];
int depth[100000];
bool flag[100000];
int heavy[100000];
int toseg[100000];
int pattop[100000];
void dfs(int node,int d)
{
	if(flag[node])
	{
		return;
	}
	flag[node]=true;
	depth[node]=d;
	for(int i=0;i<pat[node].size();i++)
	{
		if(!flag[pat[node][i]])
		{
			dfs(pat[node][i],d+1);
			ko[node].push_back(pat[node][i]);
			par[0][pat[node][i]]=node;
		}
	}
}
int num;
void lcainit()
{
	for(int i=1;i<=18;i++)
	{
		for(int j=0;j<num;j++)
		{
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}
}
int lca(int a,int b)
{
	if(a==-1)
	{
		return b;
	}
	if(b==-1)
	{
		return a;
	}
	if(depth[a]>depth[b])
	{
		swap(a,b);
	}
	for(int i=18;i>=0;i--)
	{
		if(depth[a]+(1<<i)<=depth[b])
		{
			b=par[i][b];
		}
	}
	if(a==b)
	{
		return a;
	}
	for(int i=18;i>=0;i--)
	{
		if(par[i][a]!=par[i][b])
		{
			a=par[i][a];
			b=par[i][b];
		}
	}
	return par[0][a];
}
int decomposit(int node)
{
	int maxi=0,rr;
	if(ko[node].empty())
	{
		heavy[node]=-1;
		return 1;
	}
	int siz=0;
	for(int i=0;i<ko[node].size();i++)
	{
		int z=decomposit(ko[node][i]);
		if(maxi<z)
		{
			maxi=z;
			rr=ko[node][i];
			siz+=z;
		}
	}
	heavy[node]=rr;
	return siz+1;
}
class lcatree
{
public:
	int seg[SIZE*2];
	void init()
	{
		for(int i=0;i<num;i++)
		{
			seg[SIZE+i]=i;
		}
		for(int i=num;i<SIZE;i++)
		{
			seg[SIZE+i]=-1;
		}
		for(int i=SIZE-1;i>=1;i--)
		{
			seg[i]=lca(seg[i*2],seg[i*2+1]);
		}
	}
	int getlca(int beg,int end,int node,int lb,int ub)
	{
		if(ub<beg||end<lb)
		{
			return -1;
		}
		if(beg<=lb&&ub<=end)
		{
			return seg[node];
		}
		return lca(getlca(beg,end,node*2,lb,(lb+ub)/2),getlca(beg,end,node*2+1,(lb+ub)/2+1,ub));
	}
};
class segtree
{
public:
	int segmin[SIZE*2];
	int segnum[SIZE*2];
	int flag[SIZE*2];
	void init()
	{
		for(int i=0;i<SIZE;i++)
		{
			segnum[SIZE+i]=1;
		}
		for(int i=SIZE-1;i>=1;i--)
		{
			segnum[i]=segnum[i*2]+segnum[i*2+1];
		}
	}
	void update(int beg,int end,int node,int lb,int ub,int num)
	{
		if(ub<beg||end<lb)
		{
			return;
		}
		if(beg<=lb&&ub<=end)
		{
			segmin[node]+=num;
			flag[node]+=num;
			return;
		}
		if(flag[node])
		{
			segmin[node*2]+=flag[node];
			segmin[node*2+1]+=flag[node];
			flag[node*2]+=flag[node];
			flag[node*2+1]+=flag[node];
			flag[node]=0;
		}
		update(beg,end,node*2,lb,(lb+ub)/2,num);
		update(beg,end,node*2+1,(lb+ub)/2+1,ub,num);
		segnum[node]=0;
		segmin[node]=min(segmin[node*2],segmin[node*2+1]);
		if(segmin[node*2]<=segmin[node*2+1])
		{
			segnum[node]+=segnum[node*2];
		}
		if(segmin[node*2]>=segmin[node*2+1])
		{
			segnum[node]+=segnum[node*2+1];
		}
	}
	int get()
	{
		if(segmin[1]!=0)
		{
			return SIZE;
		}
		return SIZE-segnum[1];
	}
};
lcatree ltree;
segtree tree;
int main()
{
	int gen;
	scanf("%d%d",&num,&gen);
	for(int i=0;i<num-1;i++)
	{
		int za,zb;
		scanf("%d%d",&za,&zb);
		za--;
		zb--;
		pat[za].push_back(zb);
		pat[zb].push_back(za);
	}
	fill(flag,flag+num,false);
	for(int i=0;i<=18;i++)
	{
		for(int j=0;j<num;j++)
		{
			par[i][j]=-1;
		}
	}
	dfs(0,0);
	lcainit();
	fill(heavy,heavy+num,-1);
	decomposit(0);
	int pt=0;
	for(int i=0;i<num;i++)
	{
		if(par[0][i]!=-1)
		{
			if(heavy[par[0][i]]==i)
			{
				continue;
			}
		}
		int now=i;
		for(;;)
		{
			toseg[now]=pt++;
			pattop[now]=i;
			now=heavy[now];
			if(now==-1)
			{
				break;
			}
		}
	}
	pt=0;
	ltree.init();
	tree.init();
	int maxi=0;
	for(int i=0;i<num;i++)
	{
		int now=i;
		for(;;)
		{
			if(now==-1)
			{
				break;
			}
			tree.update(toseg[pattop[now]],toseg[now],1,0,SIZE-1,1);
			now=par[0][pattop[now]];
		}
		for(;;)
		{
			int l=ltree.getlca(pt,i,1,0,SIZE-1);
			if(tree.get()-depth[l]>gen)
			{
				int n=pt;
				for(;;)
				{
					if(n==-1)
					{
						break;
					}
					tree.update(toseg[pattop[n]],toseg[n],1,0,SIZE-1,-1);
					n=par[0][pattop[n]];
				}
				pt++;
			}
			else
			{
				maxi=max(maxi,i-pt+1);
				break;
			}
			if(pt>i)
			{
				break;
			}
		}
	}
	printf("%d\n",maxi);
}