#include<bits/stdc++.h>
#include<atcoder/string>

using namespace std;
using namespace atcoder;

using psv=pair<string,vector<int>>;

bool comp(const psv &x,const psv &y){
  int xl=x.first.size(),yl=y.first.size();
  if(xl>=yl){
    for(int i=0;i<yl;i++){
      if(x.first[i] != y.first[i]){
        return (x.first[i] < y.first[i]);
      }
    }

    if(xl!=yl && x.second[yl]<(xl-yl)){
      return (x.first[yl+x.second[yl]]<x.first[x.second[yl]]);
    }

    for(int i=0;i<yl;i++){
      if(y.first[i] != x.first[i+(xl-yl)]){
        return (y.first[i] < x.first[i+(xl-yl)]);
      }
    }
  }
  else{
    for(int i=0;i<xl;i++){
      if(x.first[i] != y.first[i]){
        return (x.first[i] < y.first[i]);
      }
    }

    if(y.second[xl]<(yl-xl)){
      return (y.first[y.second[xl]]<y.first[xl+y.second[xl]]);
    }

    for(int i=0;i<xl;i++){
      if(y.first[i+(yl-xl)] != x.first[i]){
        return (y.first[i+(yl-xl)] < x.first[i]);
      }
    }
  }
  return false;
}

string concat(vector<psv> &s){
  string res="";
  for(auto &nx : s){ res+=nx.first; }
  return res;
}

int main(){
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    vector<psv> s(n);
    for(auto &nx : s){
      cin >> nx.first;
      nx.second=z_algorithm(nx.first);
    }
    sort(s.begin(),s.end(),comp);

    if(n==2){
      cout << s[1].first+s[0].first << "\n";
      continue;
    }
    
    bool ok=false;
    for(int i=1;i<n;i++){
      if(s[i-1].first+s[i].first == s[i].first+s[i-1].first){ok=true; break;}
    }
    if(ok){
      cout << concat(s) << "\n";
      continue;
    }

    swap(s[n-1],s[n-2]);
    string c1=concat(s);
    swap(s[n-1],s[n-2]);
    swap(s[n-2],s[n-3]);
    cout << min(c1,concat(s)) << "\n";
  }
  return 0;
}

// wd sothsi orw owrwo wk wr and hweorsdotus shtiso w
// w