#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;

const int maxn = 2010;

int n, m, tot = 0;


// how to  detemrien thsi 
int a[maxn], b[maxn], c[maxn], d[maxn], mx[maxn * maxn];

struct Node{
	int x, y;
	
	bool operator < (const Node &t) const{
		return x < t.x;
	}
}node[maxn * maxn];

ll read(){ ll s = 0, f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); } while(ch >= '0' && ch <= '9'){ s = s * 10 + ch - '0'; ch = getchar(); } return s * f; }

int main(){
	n = read(), m = read();
	for(int i = 1 ; i <= n ; ++i) a[i] = read(), b[i] = read();
	for(int i = 1 ; i <= m ; ++i) c[i] = read(), d[i] = read();
	
	// n * m 个条件都要满足 
	for(int i = 1 ; i <= n ; ++i){
		for(int j = 1 ; j <= m ; ++j){
			if(a[i] <= c[j] && b[i] <= d[j]) {
				node[++tot].x = c[j] - a[i] + 1;
				node[tot].y = d[j] - b[i] + 1;
			}
		}
	}
	
	sort(node + 1, node + 1 + tot);	
	
	for(int i = tot ; i >= 0 ; --i){
		mx[i] = max(mx[i + 1], node[i].y); 
	}
	
//	printf("node:\n");
//	for(int i = 1 ; i <= tot ; ++i) printf("%d %d\n", node[i].x, node[i].y); printf("\n");
//	for(int i = 1 ; i <= tot ; ++i) printf("%d ", mx[i]); printf("\n");
	
	int ans = 1000000007;
	int j = 0;
	for(int i = 0 ; i <= 1000001 ; ++i){
		while(node[j + 1].x <= i && j < tot) ++j;
//		printf("%d %d\n", i, j);
		ans = min(ans, i + mx[j + 1]);
	}
	
	printf("%d\n", ans);
	
	return 0;
}