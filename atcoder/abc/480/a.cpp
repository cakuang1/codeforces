#include "bits/stdc++.h"

using namespace std;
using ll=long long;

int main(){
    string S,T,ST;
    cin>>S>>T;
    ST=S+T;
    int a=ST.find('A');
    int d=ST.find('D');
    if(a%2==d%2||a/2==d/2){
        cout<<"Yes"<<"\n";
    }
    else{
        cout<<"No"<<"\n";
    }
}
