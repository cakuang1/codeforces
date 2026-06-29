#include <bits/stdc++.h>
using namespace std;

struct Info {
    int centroid;
    int bucket;
    int dist;
};

int n;
vector<vector<int>> g;
vector<int> sz, cdPar;
vector<bool> removed;
vector<vector<Info>> pathInfo;

vector<multiset<int>> bucketVals;
vector<int> bucketCentroid;

vector<multiset<int>> bests;
vector<int> cand;
multiset<int> globalAns;
vector<bool> black;

void dfsSize(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p || removed[v]) continue;
        dfsSize(v, u);
        sz[u] += sz[v];
    }
}

int findCentroid(int u, int p, int total) {
    for (int v : g[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] > total / 2) {
            return findCentroid(v, u, total);
        }
    }
    return u;
}

int newBucket(int c) {
    int id = bucketVals.size();
    bucketVals.push_back(multiset<int>());
    bucketCentroid.push_back(c);
    return id;
}

void collect(int u, int p, int d, int c, int bucket) {
    pathInfo[u].push_back({c, bucket, d});

    for (int v : g[u]) {
        if (v == p || removed[v]) continue;
        collect(v, u, d + 1, c, bucket);
    }
}

int getCandidate(int c) {
    if ((int)bests[c].size() < 2) return 0;

    auto it = bests[c].rbegin();
    int a = *it;
    ++it;
    int b = *it;

    return a + b;
}

void eraseOne(multiset<int>& ms, int x) {
    auto it = ms.find(x);
    if (it != ms.end()) ms.erase(it);
}

int decompose(int start, int parent) {
    dfsSize(start, -1);

    int c = findCentroid(start, -1, sz[start]);

    cdPar[c] = parent;
    removed[c] = true;

    // bucket for centroid itself
    int selfBucket = newBucket(c);
    pathInfo[c].push_back({c, selfBucket, 0});

    // buckets for each component after removing c
    for (int v : g[c]) {
        if (removed[v]) continue;

        int bucket = newBucket(c);
        collect(v, c, 1, c, bucket);
    }

    for (int v : g[c]) {
        if (removed[v]) continue;
        decompose(v, c);
    }

    return c;
}

void updateNode(int x, bool add) {
    for (auto [c, bucket, d] : pathInfo[x]) {
        eraseOne(globalAns, cand[c]);

        if (!bucketVals[bucket].empty()) {
            eraseOne(bests[c], *bucketVals[bucket].rbegin());
        }

        if (add) {
            bucketVals[bucket].insert(d);
        } else {
            eraseOne(bucketVals[bucket], d);
        }

        if (!bucketVals[bucket].empty()) {
            bests[c].insert(*bucketVals[bucket].rbegin());
        }

        cand[c] = getCandidate(c);
        globalAns.insert(cand[c]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    g.assign(n + 1, {});
    sz.assign(n + 1, 0);
    cdPar.assign(n + 1, -1);
    removed.assign(n + 1, false);
    pathInfo.assign(n + 1, {});
    bests.assign(n + 1, {});
    cand.assign(n + 1, 0);
    black.assign(n + 1, false);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    decompose(1, -1);

    for (int i = 1; i <= n; i++) {
        globalAns.insert(0);
    }

    // initially all black
    for (int i = 1; i <= n; i++) {
        black[i] = true;
        updateNode(i, true);
    }


    /
    int q;
    cin >> q;

    while (q--) {
        int x;
        cin >> x;

        if (black[x]) {
            black[x] = false;
            updateNode(x, false);
        } else {
            black[x] = true;
            updateNode(x, true);
        }

        cout << *globalAns.rbegin() << '\n';
    }

    return 0;
}