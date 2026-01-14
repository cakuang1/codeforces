#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define ll long long

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<pair<ll, int>> query;
  for (int i = 0; i < q; i++) {
    ll k;
    cin >> k;
    query.push_back({k - 1, i});
  }

  sort(query.rbegin(), query.rend());
  vector<pair<int, int>> ans(q);

  ordered_set<pair<int, int>> S;
  for (int i = 0; i < n; i++) {
    S.insert({a[i], -i});
  }

  // B_k < A
  ll cnt = 0;
  for (int l = 0; l < n; l++) {
    S.erase({a[l], -l});
    ll lim = S.order_of_key({a[l], -(1 << 30)});
    while (!query.empty()) {
      auto [k, qi] = query.back();

      ll k1 = k - cnt;
      if (k1 < lim) {
        ans[qi] = {l, -(*S.find_by_order(k1)).second};
        query.pop_back();
      } else {
        break;
      }
    }
    cnt += lim;
  }

  // B_k = A
  {
    vector<int> C(n + 1, 0), idx(n + 1, -1);
    pair<int, int> p;
    for (int i = 0; i < n; i++) {
      if (idx[a[i]] != -1) {
        p = {idx[a[i]], i};
      }
      cnt += C[a[i]];
      C[a[i]]++;
      idx[a[i]] = i;
    }
    while (!query.empty()) {
      auto [k, qi] = query.back();
      if (k < cnt) {
        ans[qi] = p;
        query.pop_back();
      } else {
        break;
      }
    }
  }

  // B_k > A
  for (int l = n - 1; l >= 0; l--) {
    int offset = S.order_of_key({a[l], 1 << 30});
    while (!query.empty()) {
      auto [k, qi] = query.back();
      int k1 = k - cnt + offset;
      if (k1 < S.size()) {
        ans[qi] = {l, (*S.find_by_order(k1)).second};
        query.pop_back();
      } else {
        break;
      }
    }
    cnt += S.size() - offset;
    S.insert({a[l], l});
  }

  for (auto [l, r] : ans) {
    cout << l + 1 << " " << r + 1 << "\n";
  }
}

// wewr