#include<bits/stdc++.h>
#include<atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
  int n,q;
  cin >> n >> q;
 
  dsu uf(n+q+5);
  int balls=n;
 
  vector<int> ld(n+1,-1);
  vector<int> inv(n+q+5);
  for(int i=1;i<=n;i++){
    ld[i]=i;
    inv[ld[i]]=i;
  }
 
  for(int tr=0;tr<q;tr++){
    int typ;
    cin >> typ;
    if(typ==1){
      int x,y;
      cin >> x >> y;
      if(ld[y]==-1){continue;}
      else if(ld[x]==-1){
        ld[x]=ld[y];
        inv[ld[x]]=x;
        ld[y]=-1;
      }
      else{
        uf.merge(ld[x],ld[y]);
        ld[x]=uf.leader(ld[x]);
        inv[ld[x]]=x;
        ld[y]=-1;
      }
    }
    if(typ==2){
      int x;
      cin >> x;
      balls++;
      if(ld[x]==-1){
        ld[x]=balls;
        inv[ld[x]]=x;
      }
      else{
        uf.merge(ld[x],balls);
        ld[x]=uf.leader(balls);
        inv[ld[x]]=x;
      }
    }
    if(typ==3){
      int x;
      cin >> x;
      int tg=uf.leader(x);
      cout << inv[tg] << "\n";
    }
  }
  return 0;
}
