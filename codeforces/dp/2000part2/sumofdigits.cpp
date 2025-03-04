//#pragma comment(linker, "/STACK:16777216") //for c++ Compiler
#include <bits/stdc++.h>
#define Max(a,b) (((a) > (b)) ? (a) : (b))
#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Abs(x) (((x) > 0) ? (x) : (-(x)))
#define MOD 1000000007
#define pi acos(-1.0)

using namespace std;

typedef long long           ll      ;
typedef unsigned long long  ull     ;
typedef unsigned int        uint    ;
typedef unsigned char       uchar   ;

template<class T> inline void checkmin(T &a,T b){if(a>b) a=b;}
template<class T> inline void checkmax(T &a,T b){if(a<b) a=b;}

const double eps = 1e-7      ;
const int N = 1              ;
const int M = 200000         ;
const ll P = 10000000097ll   ;
const int INF = 0x3f3f3f3f   ;

int b1, b2;
int a[1000], len;

void output(){
    for(int i = len; i >= 1; --i){
        printf("%d",a[i]);
    }
    puts("");
}

void add(int num){
    int i = 1;
    while(num){
        if(9 == a[i]){
            ++i;
        }
        else{
            ++a[i];
            --num;
        }
    }
    checkmax(len, i);
}

void add_new(int num){
    int i = 1;
    while(num <= 0){
        num += a[i];
        a[i++] = 0;
    }
    while(9 == a[i]){
        num += a[i];
        a[i++] = 0;
    }
    ++a[i];
    --num;
    checkmax(len, i);
    add(num);
}


// 

int main(){
    int i, j, t, n, m;
    while(EOF != scanf("%d",&t)){
        memset(a, 0, sizeof(a));
        len = 1;
        scanf("%d",&b1);
        add(b1);
        output();
        for(i = 1; i < t; ++i){
            scanf("%d",&b2);
            int delta = b2 - b1;
            b1 = b2;
            if(delta > 0)   add(delta);
            else    add_new(delta);
            output();
        }

    }

}