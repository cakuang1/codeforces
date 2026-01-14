#include<cstdio>
#include<cctype>
#include<climits>
#include<algorithm>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
typedef long long int64;
const int N=2e5+1,M=2e5;
int c[N];
int64 f[N];
struct Segment {
	int l,r,p;
	bool operator < (const Segment &rhs) const {
		return r<rhs.r;
	}
};
Segment s[M];
class SegmentTree {
	#define _left <<1
	#define _right <<1|1
	#define mid ((b+e)>>1)
	private:
		int64 val[N<<2],tag[N<<2];
		void push_up(const int &p) {
			val[p]=std::max(val[p _left],val[p _right]);
		}
		void push_down(const int &p) {
			if(tag[p]==0) return;
			tag[p _left]+=tag[p];
			tag[p _right]+=tag[p];
			val[p _left]+=tag[p];
			val[p _right]+=tag[p];
			tag[p]=0;
		}
	public:
		void modify(const int &p,const int &b,const int &e,const int &l,const int &r,const int64 &x) {
			if(b==l&&e==r) {
				val[p]+=x;
				tag[p]+=x;
				return;
			}
			push_down(p);
			if(l<=mid) modify(p _left,b,mid,l,std::min(mid,r),x);
			if(r>mid) modify(p _right,mid+1,e,std::max(mid+1,l),r,x);
			push_up(p);
		}
		int64 query(const int &p,const int &b,const int &e,const int &l,const int &r) {
			if(b==l&&e==r) return val[p];
			push_down(p);
			int64 ret=0;
			if(l<=mid) ret=std::max(ret,query(p _left,b,mid,l,std::min(mid,r)));
			if(r>mid) ret=std::max(ret,query(p _right,mid+1,e,std::max(mid+1,l),r));
			return ret;
		}
	#undef _left
	#undef _right
	#undef mid
};
SegmentTree t;
int main() {
	const int n=getint(),m=getint();
	for(register int i=1;i<=n;i++) c[i]=getint();
	for(register int i=0;i<m;i++) {
		const int l=getint(),r=getint(),p=getint();
		s[i]=(Segment){l,r,p};
	}
	std::sort(&s[0],&s[m]);
	for(register int i=1,j=0;i<=n;i++) {
		t.modify(1,0,n,0,i-1,-c[i]);
		for(;j<m&&s[j].r<=i;j++) {
			t.modify(1,0,n,0,s[j].l-1,s[j].p);
		}
		f[i]=std::max(f[i-1],t.query(1,0,n,0,i-1));
		t.modify(1,0,n,i,i,f[i]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
