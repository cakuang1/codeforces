#include <bits/stdc++.h>

using namespace std;

vector<string> v;
char buf[5002];
int main(){
    scanf("%s",buf);
    string s=buf;
    for(int i=0;i<s.size();i++){
        for(int j=i;j<s.size()&&j<i+7;j++){
            v.push_back(s.substr(i,j-i+1));
        }
    }
    sort(v.begin(),v.end());
    int k;
    cin>>k;
    k--;
    v.erase(unique(v.begin(),v.end()),v.end());
    printf("%s\n",v[k].c_str());
    return 0;
}