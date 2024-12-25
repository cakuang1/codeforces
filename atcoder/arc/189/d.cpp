#include<iostream>
#include<cassert>
#include<atcoder/segtree>
using namespace std;
int op(int a,int b){return max(a,b);}
int e(){return 0;}
int N,A[5<<17];
long S[5<<17];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N;
	for(int i=0;i<N;i++)
	{
		cin>>A[i];
		S[i+1]=S[i]+A[i];
	}
	atcoder::segtree<int,op,e>seg(vector<int>(A,A+N));
	for(int k=0;k<N;k++)
	{
		int l=k,r=k+1;
		while(0<l||r<N)
		{
			long cur=S[r]-S[l];
			int nr=seg.max_right(r,[&](int x){return x<cur;});
			int nl=seg.min_left(l,[&](int x){return x<cur;});
			if(l==nl&&r==nr)break;
			l=nl;
			r=nr;
		}
		cout<<S[r]-S[l]<<(k+1==N?"\n":" ");
	}
}


//