#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  scanf("%d",&n);
  static long long A[100000];
  for(int i=0;i<n;i++){
    scanf("%lld",A+i);
  }
  sort(A,A+n);
  long long S=A[0];
  int x=0;
  for(int i=1;i<n;i++){
    if(2*S<A[i]){
      x=i;
    }
    S+=A[i];
  }
  printf("%d\n",n-x);
  return 0;
}
