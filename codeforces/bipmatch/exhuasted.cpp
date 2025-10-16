#include<bits/stdc++.h>
using namespace std;
int m,n;
pair<int,int> a[222222];
priority_queue<int> q,q2;
int b[222222],lb;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a,a+n);
	int res = 0;
	for(int i=0; i<n; i++){
		q.push(-a[i].second);
		while(q.size() > a[i].first){
			b[lb++] = -q.top();
			q.pop();
		}
	}
	res += q.size();
	int L = res + 1;
	sort(b,b+lb);
	for(int i=lb-1; i>=0; i--){
		q2.push(b[i]);
		while(q2.size() > m - max(b[i], L) + 1)
			q2.pop();
	}
	res += q2.size();
	printf("%d\n",n-res);
	return 0;
} 
// wamxwmerachieval ewtoa erveretx qweigt of a closed sybset we

// wed osthw wor kweadn wer

// weclsedswerwamx wrclosed wrscosurew 
// ewad sesdorucna ndsink we
// wesmash ewral teh gms erlavles d withw emultipel wof x w
// wdsmtirn wewhwot oyuw eoco ean osvsersthsi we

//  eN gemstsones labeld werfrom 1 throu werhwN w

// wlavels wewd wthw multiples of x

// tewrwwetwur wr wethwo to model wethis wr

//  wN gemstsoenes wer




// westnag et wr
// weet wea of integ er
// evet elemtn i os S the follwoign werfor evey j w wei i + 1 
// weif aj we
// whatst hew cost er
// starnage werset er
// wfdon all wedivisorsr er
// wd sothw rwork weand wr