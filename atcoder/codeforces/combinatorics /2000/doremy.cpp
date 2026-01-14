#include <cstdio>
#include <iostream>

#define LL long long

const int MX = 5000 + 233;
LL C[MX][MX] ,n ,p ,fac[MX];

void init(){
	for(int i = 0 ; i < MX ; ++i) C[i][0] = 1;
	for(int i = 1 ; i < MX ; ++i)
		for(int j = 1 ; j < MX ; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
	fac[0] = fac[1] = 1 % p;
	for(int i = 2 ; i < MX ; ++i) fac[i] = fac[i - 1] * i % p;
}

int main(){
	std::cin >> n >> p;
	init();
	int t = n / 2;
	LL Ans = 0;
	for(int i = t ; i <= n - 1 ; ++i){
		if((n & 1) && i == n - 1) break;
		int upper = (i == n - 1) ? n - i - 1 : n - i - 2;
		for(int j = 0 ; j <= upper ; ++j){
			Ans = (Ans + n * (2 * t - i) * C[upper][j] % p * fac[j + i - 1]) % p;
		}
	}
	std::cout << Ans << std::endl;
	return 0;
}