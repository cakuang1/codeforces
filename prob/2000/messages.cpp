#include <bits/stdc++.h>     

using namespace std;

const int N = 200043;
const int K = 20;
vector<int> idx[N];
int m[N], k[N];

bool frac_greater(pair<int, int> a, pair<int, int> b)
{
    return a.first * b.second > a.second * b.first;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &m[i], &k[i]);
        idx[m[i]].push_back(i);
    }

    vector<int> cert;
    pair<int, int> ans = {0, 1};
    for(int i = 1; i <= K; i++)
    {
        vector<int> score(N);
        for(int j = 0; j < n; j++)
            score[m[j]] += min(i, k[j]);
        vector<pair<int, int>> aux;
        for(int j = 0; j < N; j++)
            aux.push_back(make_pair(score[j], j));
        sort(aux.rbegin(), aux.rend());
        pair<int, int> cur_ans = {0, i};
        vector<int> cur_cert;
        for(int j = 0; j < i; j++)
        {
            cur_ans.first += aux[j].first;
            cur_cert.push_back(aux[j].second);
        }
        if(frac_greater(cur_ans, ans))
        {
            ans = cur_ans;
            cert = cur_cert;
        }
    }
    cout << cert.size() << endl;
    shuffle(cert.begin(), cert.end(), mt19937(time(NULL)));
    for(auto x : cert) cout << x << " ";
    cout << endl;
}