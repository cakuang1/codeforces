using namespace std ;

#define int long long

const int MAXN = 1e5 + 100 ;

vector<int>ver[MAXN] , com[MAXN] , ps[MAXN] ; 
int vis[MAXN] , dis[MAXN] ; 
int mxr , mxid ; 
void dfs(int v , int col = -1 , int h = 0 , int par = -1){
	vis[v] = max(vis[v] , col) ; 
	if(mxr < h)mxid = v , mxr = h ; 
	dis[v] = max(h , dis[v]) ; 
	if(col > 0)com[col] . push_back(dis[v]) ; 
	for(auto u : ver[v]){
		if(u == par)continue ; 
		dfs(u , col , h + 1 , v) ; 
	}
}
map<pair<int , int> , int> check ;
int32_t main(){
    ios_base::sync_with_stdio(0) ;
    cin . tie(0) ; cout . tie(0) ;
    int n , m , q ; cin >> n >> m >> q ; 
    for(int i = 0 ; i < m ; i ++){
    	int x , y ; cin >> x >> y ; 
    	x -- , y -- ; 
    	ver[x] . push_back(y) ; 
    	ver[y] . push_back(x) ;
    }
    int cnt = 0 ; 
    for(int i = 0 ; i < n ; i ++){
    	if(vis[i])continue ; 
    	mxr = 0 , mxid = i ; 
    	dfs(i) ; 
    	mxr = 0 ; 
    	dfs(mxid) ;
    	dfs(mxid , ++ cnt) ; sort(com[cnt] . begin() , com[cnt] . end()) ; 
    	ps[cnt] . push_back(0) ; 
    	for(auto v : com[cnt])ps[cnt] . push_back(ps[cnt] . back() + v) ; 
    }
	cout << fixed << setprecision(10) ;
    while(q --){
    	int x , y ; cin >> x >> y ; 
    	x -- , y -- ; x = vis[x] ; y = vis[y] ; 
    	if(com[x] . size() > com[y] . size())swap(x , y) ; 
    	if(x == y){cout << -1 << '\n' ; continue ; }
    	if(check[{x , y}] > 0){cout << double(check[{x , y}]) / (1ll * com[x] . size() * com[y] . size()) << '\n' ; continue ; }
    	int ans = 0 , mxd = max(com[x] . back() , com[y] . back()) ; 
    	for(auto v : com[x]){
    		int num = lower_bound(com[y] . begin() , com[y] . end() , mxd - v - 1) - com[y] . begin() ; 
    		ans += num * mxd + (com[y] . size() - num) *  (v + 1) + ps[y] . back() - ps[y][num] ; 
    	}
    	check[{x , y}] = ans ; 
    	cout << double(check[{x , y}]) / (1ll * com[x] . size() * com[y] . size()) << '\n' ; 
    }
} 