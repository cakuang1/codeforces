#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

#define endl '\n'
#define int long long


//struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//    }
//}rng;

int mod=998244353;
int n,m;
vector<int>g[51];
vector<pair<int,int>>medges;
map<pair<int,int>,int>ei;

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int ttt=1;
    //cin>>ttt;
    while(ttt--)
    {
        cin>>n;
        for(int i=0; i<n-1; i++)
        {
            int x,y;
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
            if(x>y)swap(x,y);
            ei[{x,y}]=i;
        }
        int tot=(1ll<<(n-1));
        cin>>m;
        for(int i=0; i<m; i++)
        {
            int x,y;
            cin>>x>>y;
            medges.push_back({x,y});
        }
        int mina=0;
        vector<int>pm(m);
        for(int i=0; i<m; i++)
        {
            vector<int>par(n+1,-1);
            vector<bool>vis(n+1,false);
            queue<int>q;
            int a=medges[i].first,b=medges[i].second;
            q.push(a);
            vis[a]=true;
            while(!q.empty())
            {
                int node=q.front();
                if(node==b)break;
                vis[node]=true;
                q.pop();
                for(auto it:g[node])
                {
                    if(!vis[it])
                    {
                        vis[it]=true;
                        q.push(it);
                        par[it]=node;
                    }
                }
            }
            int now=b;
            int mask=0;
            while(1)
            {
                int pnow=par[now];
                if(pnow==-1)break;
                int x=now,y=pnow;
                if(x>y)swap(x,y);
                mask|=(1ll<<ei[{x,y}]);
                now=pnow;
            }
            //cout<<"mask "<<mask<<endl;
            pm[i]=mask;
        }
        for(int i=1; i<(1ll<<m); i++)
        {
            int mask=0;
            for(int j=0; j<m; j++)if((1ll<<j)&i)mask|=pm[j];
            int bc=__builtin_popcountl(mask);
            int left=n-1-bc;
            int ways=(1ll<<left);
            //cout<<"mask bc left ways "<<mask<<" "<<bc<<" "<<left<<" "<<ways<<endl;
            if(__builtin_popcountl(i)&1)tot-=ways;
            else tot+=ways;
        }
        cout<<tot;
    }
    return 0;
}

// wcd w wfor 

