#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;


int main()
{
    int T;
    cin>>T;
    for (int t=0; t<T; t++)
    {
        int N;
        cin>>N;
        vector<vector<int>> E(N);
        for (int i=0; i<N-1; i++)
        {
            int A, B;
            cin>>A>>B;
            E[A-1].push_back(B-1);
            E[B-1].push_back(A-1);
        }
        string S;
        cin>>S;

        string ans(N, '.');
        vector<int> X(N);
        function<void(int, int)> f = [&](int c, int p)
        {
            int b = 0;
            int w = 0;
            int x = 3;

            for (int e: E[c])
                if (e!=p)
                {
                    f(e, c);
                    (ans[e]=='W'?w:b)++;
                    x &= X[e];
                }

            if (x==0)
            {
                X[c] = 0;
                ans[c] = 'X';
            }
            else
            {
                switch (x)
                {
                case 1:
                    ans[c] = 'B';
                    break;
                case 2:
                    ans[c] = 'W';
                    break;
                case 3:
                    if (p==-1)
                        ans[c] = 'B';
                    else
                        ans[c] = S[p];
                }

                if (b==w)
                {
                    if (S[c]=='B')
                        X[c] = 1;
                    else
                        X[c] = 2;
                }
                else
                {
                    if (b>w && S[c]=='B' || w>b && S[c]=='W')
                        X[c] = 3;
                    else
                        X[c] = 0;
                }
            }
        };
        f(0, -1);

        if (X[0]==0)
            cout<<-1<<endl;
        else
            cout<<ans<<endl;
    }
}
