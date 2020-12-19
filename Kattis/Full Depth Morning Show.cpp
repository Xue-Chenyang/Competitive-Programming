#include <bits/stdc++.h>
using namespace std;
typedef pair<long, long> ii;

#define MAXN 100005

long long tot[MAXN], tax[MAXN], child[MAXN], tsum[MAXN], taxamt[MAXN], tot_tax = 0;
long long d[MAXN], n;
vector<vector<ii>> adj;

long long dfs(int u, int par) {
    child[u] = 1;
    tot_tax += tax[u];
    tsum[u] = tax[u];
    for (ii &p : adj[u]) {
        if (p.first == par) continue;
        d[p.first] = d[u] + p.second;
        child[u] += dfs(p.first, u);
        tsum[u] += tsum[p.first];
    }
    //cout << u << ": " << child[u] << endl;
    return child[u];
}

void dfs2(int u, int par) {
    for (ii &p : adj[u]) {
        long v,w; tie(v,w) = p;
        if (v == par) continue;
        tot[v] = tot[u] + w * (n - 2 * child[v]);
        taxamt[v] = taxamt[u] + w * (tot_tax - 2 * tsum[v]);
        dfs2(v, u);
    }
}

int main() {
    cin >> n;
    for (int i= 0; i < n; i++) cin >> tax[i];
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a,b,w; cin >> a >> b >> w;
        adj[a - 1].push_back({b - 1, w});
        adj[b - 1].push_back({a - 1, w});
    }
    d[0] = 0;
    dfs(0, -1);
    for (int i = 0; i < n; i++) tot[0] += d[i], taxamt[0] += d[i] * tax[i];
    dfs2(0,-1);
    for (int i = 0; i < n; i++) {
        //cout << "v: " << i << " " << tax[i] * tot[i] << " " << taxamt[i] << endl;
        cout << tax[i] * tot[i] + taxamt[i] << '\n';
    }
}