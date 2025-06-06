//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
 
#define y1 y114514
int T, n, m, x1, y1, x2, y2;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int f(int x, int y) {
	if((x == 1 || x == n) && (y == 1 || y == m)) return 2;
	if(x == 1 || x == n || y == 1 || y == m) return 3;
	return 4;
}
 
int main() {
	for(scanf("%d", &T);T;T--) {
		scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
		printf("%d\n", min(f(x1, y1), f(x2, y2)));
	}
	return 0;
}