#include<bits/stdc++.h>

using namespace std;

string go(string t)
{
    while(t.back() == '0') t.pop_back();
    reverse(t.begin(), t.end());
    return t;
}

string to_bin(long long x)
{
    if(x == 0)
        return "";
    else
    {
        string s = to_bin(x / 2);
        s.push_back(char('0' + x % 2));
        return s;
    }
}

int main()
{
    long long x, y;
    cin >> x >> y;
    set<string> used;
    queue<string> q;
    q.push(to_bin(x));
    used.insert(to_bin(x));
    while(!q.empty())
    {
        string k = q.front();
        q.pop();
        if(k.size() > 100) continue;
        for(int i = 0; i < 2; i++)
        {
            string k2 = go(k + string(1, char('0' + i)));
            if(!used.count(k2))
            {
                used.insert(k2);
                q.push(k2);
            }
        }
    }
     if(used.count(to_bin(y)))
        cout << "YES\n";
    else
        cout << "NO\n";
}