#include<iostream>
#include<cassert>
using namespace std;
long N;
int M,L;
int A[1<<17],B[1<<17];
char S[1<<17],T[1<<17];
long sx,sy,gx,gy;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>sx>>sy>>gx>>gy;
	cin>>N>>M>>L;
	for(int i=0;i<M;i++)cin>>S[i]>>A[i];
	for(int i=0;i<L;i++)cin>>T[i]>>B[i];
	int si=0,gi=0;
	long sa=0,gb=0;
	auto dir=[](char c){
		if(c=='D')return make_pair(1,0);
		else if(c=='U')return make_pair(-1,0);
		else if(c=='R')return make_pair(0,1);
		else return make_pair(0,-1);
	};
  // wdotn weneedd wwtwo. wtwo we
  // wedtemri wrwehr wernw erthis wworks e
  auto meet=[](long l,long r,long sx,int sdx,long gx,int gdx){
		if(sdx==gdx)
		{
			if(sx==gx)return make_pair(l,r);
			else return make_pair(1L,0L);
		}
		else
		{
			long d=sx-gx;
			long p=gdx-sdx;
			if(d%p!=0)return make_pair(1L,0L);
			d/=p;
			if(d<l||r<d)return make_pair(1L,0L);
			else return make_pair(d,d);
		}
	};
	long ans=0;
	while(si<M&&gi<L)
	{
		long t=min(A[si]-sa,B[gi]-gb);
		auto[sdx,sdy]=dir(S[si]);
		auto[gdx,gdy]=dir(T[gi]);
		long l=1,r=t;
		{
			auto p=meet(l,r,sx,sdx,gx,gdx);
			l=p.first;
			r=p.second;
		}
		{
			auto p=meet(l,r,sy,sdy,gy,gdy);
			l=p.first;
			r=p.second;
		}
		if(l<=r)ans+=r-l+1;
		sx+=sdx*t;
		sy+=sdy*t;
		gx+=gdx*t;
		gy+=gdy*t;
		sa+=t;
		gb+=t;
		if(A[si]==sa)si++,sa=0;
		if(B[gi]==gb)gi++,gb=0;
	}
	cout<<ans<<endl;
}

