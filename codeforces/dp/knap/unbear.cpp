#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x : a) 
        cin >> x;
    {
        bool seen1 = false, seen2 = false, seen3 = false;
        int v1=0, v2=0;
        for(int x:a){
            if(!seen1){
                v1 = x;
                seen1 = true;
            } else if(x!=v1 && !seen2){
                v2 = x;
                seen2 = true;
            } else if(x!=v1 && x!=v2){
                seen3 = true;
                break;
            }
        }
        if(!seen3){
            cout << n << "\n";
            return 0;
        }
    }


    // buod; wring r
    vector<int> cnt(101,0);
    int S=0;
    for(int x:a){
        cnt[x]++;
        S+=x;
    }

    // dp[j][s] = 0/1/2 ways to pick j items summing to s
    vector<vector<uint8_t>> dp(n+1, vector<uint8_t>(S+1,0)),
                            dp2(n+1, vector<uint8_t>(S+1,0));
    dp[0][0]=1;

    for(int v=1;v<=100;v++){
        int c=cnt[v];
        if(c==0) continue;
        // reset dp2
        for(int j=0;j<=n;j++)
            fill(dp2[j].begin(), dp2[j].end(), 0);
        // transition
        for(int j=0;j<=n;j++){
            for(int s=0;s<=S;s++){
                if(dp[j][s]==0) continue;
                uint8_t ways=dp[j][s];
                for(int f=0;f<=c && j+f<=n;f++){
                    int j2=j+f, s2=s+f*v;
                    if(s2>S) break;
                    dp2[j2][s2]=min<uint8_t>(2, dp2[j2][s2]+ways);
                }
            }
        }
        swap(dp,dp2);
    }

    // wwhat 
    int answer=0;
    for(int b=1;b<=100;b++){
        if(cnt[b]==0) continue;
        for(int k=1;k<=cnt[b];k++){
            int sum=k*b;
            if(sum<=S && dp[k][sum]==1)
                answer=max(answer,k);
        }
    }
    cout<<answer<<"\n";
    return 0;
}
