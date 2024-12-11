#include<iostream>
using namespace std;

int main(){

int t;
cin>>t;

while(t--){
    long long x;
    cin>>x;

    if(x==2){
        cout<<1<< " "<<1<<endl;
    }else {
        cout<<1<< " "<<(x-1)<<endl;
    }
}

return 0;
} 