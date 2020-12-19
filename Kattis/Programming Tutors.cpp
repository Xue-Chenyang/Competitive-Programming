#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;

vector<int> vis, match;
vector<vector<int>> adj;
int aug(int L) {
    if (vis[L]) return 0;
    vis[L]= 1 ;
    for (auto& R : adj[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

int n;
int main() {
    cin >> n;
    vector<ii> st(n), t(n);
    ll D[105][105];
    for (int i = 0; i < n; i ++) {
        cin >> st[i].first >> st[i].second;
    }
    for (int i = 0; i < n; i ++) {
        cin >> t[i].first >> t[i].second;
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            D[i][j] = abs(st[i].first - t[j].first) + abs(st[i].second - t[j].second);
        }
    }
    ll left = 0, right = 1e10;
    while (left < right) {
        ll mid = (left + right) / 2;
        adj.assign(n, vector<int>());
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (D[i][j] <= mid) {
                    adj[i].push_back(j);
                }
            }
        }
        unordered_set<int> freeV;
        for (int L = 0; L < n; L++) {
            freeV.insert(L);
        }
        match.assign(n,-1);
        int MCBM = 0;
        for (int L = 0; L < n; L++) {
            vector<int> cs;
            for (auto & R : adj[L]) {
                if (match[R] == -1) cs.push_back(R);
            }
            if (!cs.empty()) {
                ++MCBM;
                freeV.erase(L);
                int a = rand() % cs.size();
                match[cs[a]] = L;
            }
        }
        for (auto & f : freeV) {
            vis.assign(n, 0);
            MCBM += aug(f);
        }
        if (MCBM == n) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << left << endl;
}
