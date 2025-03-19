#include <bits/stdc++.h>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define LL long long
#define rep1(i,a,b) for (int i = a;i <= b;i++)
#define rep2(i,a,b) for (int i = a;i >= b;i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ms(x,y) memset(x,y,sizeof x)
#define Open() freopen("F:\\rush.txt","r",stdin)
#define Close() ios::sync_with_stdio(0),cin.tie(0)

typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

const int dx[9] = {0,1,-1,0,0,-1,-1,1,1};
const int dy[9] = {0,0,0,-1,1,-1,1,-1,1};
const double pi = acos(-1.0);
const int N = 110;

LL k,x,n,m;

LL check2(int now,LL ac1,LL ac2,int st1,int en1,int st2,int en2){
    if (ac2>x) return ac2;
    if (now==k) return ac2;
    return check2(now+1,ac2,ac1 + ac2 + ( (en1 && st2)?1:0),st2,en2,st1,en2);
}

bool check(LL ac1,LL ac2,int st1,int en1,int st2,int en2){
    if (ac1*2 + st1 + en1>n) return false;
    if (ac2*2 + st2 + en2>m) return false;
    if (check2(2,ac1,ac2,st1,en1,st2,en2)==x) return true;
    return false;
}

string create(int ac,int st,int en,int len){
    string s;
    s.resize(len);
    int l = 0;
    if (st) s[l++] = 'C';
    if (en) s[--len] = 'A';
    while (ac--){
        s[l++] = 'A';
        s[l++] = 'C';
    }
    while (l<len) s[l++] = 'X';
    return s;
}

int main(){
    //Open();
    Close();
    cin >> k >> x >> n >> m;
    rep1(ac1,0,n/2)
        rep1(ac2,0,m/2)
            rep1(i,0,15)
            if (check(ac1,ac2,(i&1)>0,(i&2)>0,(i&4)>0,(i&8)>0)){
                cout << create(ac1,(i&1)>0,(i&2)>0,n) << endl;
                cout << create(ac2,(i&4)>0,(i&8)>0,m) << endl;
                return 0;
            }
    cout <<"Happy new year!"<<endl;
    return 0;
}