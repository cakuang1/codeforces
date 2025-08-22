#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = (1LL<<60);

struct State {
    int A, B;
    ll dist;
};
struct Cmp {
    bool operator()(State const &x, State const &y) const {
        return x.dist > y.dist;
    }
};

// simple gcd for C++11
int mygcd(int x, int y) {
    while (y) {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a,b,x;
    cin >> a >> b >> x;
    if (x % mygcd(a,b) != 0) {
        cout << "-1\n";
        return 0;
    }

    // Dijkstra on states (A,B)
    vector<vector<ll>> dist(a+1, vector<ll>(b+1, INF));
    vector<vector<pair<int,int>>> prv(a+1, vector<pair<int,int>>(b+1, make_pair(-1,-1)));
    vector<vector<int>> op(a+1, vector<int>(b+1, -1));

    priority_queue<State, vector<State>, Cmp> pq;
    dist[0][0] = 0;
    pq.push(State{0,0,0});

    int endA=-1, endB=-1;
    while(!pq.empty()){
        State s = pq.top(); pq.pop();
        int A = s.A, B = s.B;
        ll d = s.dist;
        if (d > dist[A][B]) continue;
        if (A == x) {
            endA = A;
            endB = B;
            break;
        }

        // 0: FILL A
        if (A < a) {
            ll w = a - A;
            if (d + w < dist[a][B]) {
                dist[a][B] = d + w;
                prv[a][B] = make_pair(A,B);
                op[a][B] = 0;
                pq.push(State{a,B,dist[a][B]});
            }
        }
        // 1: FILL B
        if (B < b) {
            ll w = b - B;
            if (d + w < dist[A][b]) {
                dist[A][b] = d + w;
                prv[A][b] = make_pair(A,B);
                op[A][b] = 1;
                pq.push(State{A,b,dist[A][b]});
            }
        }
        // 2: EMPTY A
        if (A > 0) {
            ll w = A;
            if (d + w < dist[0][B]) {
                dist[0][B] = d + w;
                prv[0][B] = make_pair(A,B);
                op[0][B] = 2;
                pq.push(State{0,B,dist[0][B]});
            }
        }
        // 3: EMPTY B
        if (B > 0) {
            ll w = B;
            if (d + w < dist[A][0]) {
                dist[A][0] = d + w;
                prv[A][0] = make_pair(A,B);
                op[A][0] = 3;
                pq.push(State{A,0,dist[A][0]});
            }
        }
        // 4: MOVE A->B
        if (A > 0 && B < b) {
            int delta = min(A, b - B);
            int nA = A - delta, nB = B + delta;
            if (d + delta < dist[nA][nB]) {
                dist[nA][nB] = d + delta;
                prv[nA][nB] = make_pair(A,B);
                op[nA][nB] = 4;
                pq.push(State{nA,nB,dist[nA][nB]});
            }
        }
        // 5: MOVE B->A
        if (B > 0 && A < a) {
            int delta = min(B, a - A);
            int nA = A + delta, nB = B - delta;
            if (d + delta < dist[nA][nB]) {
                dist[nA][nB] = d + delta;
                prv[nA][nB] = make_pair(A,B);
                op[nA][nB] = 5;
                pq.push(State{nA,nB,dist[nA][nB]});
            }
        }
    }

    if (endA < 0) {
        cout << "-1\n";
        return 0;
    }

    // Reconstruct
    vector<string> moves;
    int A = endA, B = endB;
    while (!(A==0 && B==0)) {
        int c = op[A][B];
        pair<int,int> p = prv[A][B];
        int pA = p.first, pB = p.second;
        switch(c) {
            case 0: moves.push_back("FILL A");   break;
            case 1: moves.push_back("FILL B");   break;
            case 2: moves.push_back("EMPTY A");  break;
            case 3: moves.push_back("EMPTY B");  break;
            case 4: moves.push_back("MOVE A B"); break;
            case 5: moves.push_back("MOVE B A"); break;
        }
        A = pA; B = pB;
    }
    reverse(moves.begin(), moves.end());

    cout << moves.size() << " " << dist[endA][endB] << "\n";
    for (size_t i = 0; i < moves.size(); i++) {
        cout << moves[i] << "\n";
    }
    return 0;
}

// wr