#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
typedef vector<vector<int>> vv;

unordered_map<string, int> rmp;
int sz = 0;
int d[MAXN], sm[MAXN];
bool vis[MAXN];
vector<string> wd;
vv adj;
void bfs(int src) {
    queue<int> q;
    vector<int> comp;
    vis[src] = true;
    int mlen = (int)(wd[src].length());
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        comp.push_back(u);
        q.pop();
        for (int &i : adj[u]) {
            if (!vis[i]) {
                vis[i] = true;
                mlen = min(mlen, (int)(wd[i].size()));
                q.push(i);
            }
        }
    }
    for (int &i : comp) sm[i] = mlen;

}

int main() {
    int n,m; cin >> n >> m;
    vector<string> v(n);
    for (string &i : v) {
        cin >> i;
        if (!rmp.count(i)) rmp[i] = sz++, adj.emplace_back(), wd.push_back(i);
    }
    for (int i = 0; i < m; i++) {
        string a,b; cin >> a >> b;
        if (!rmp.count(a)) rmp[a] = sz++, adj.emplace_back(), wd.push_back(a);
        if (!rmp.count(b)) rmp[b] = sz++, adj.emplace_back(), wd.push_back(b);
        adj[rmp[a]].push_back(rmp[b]);
        adj[rmp[b]].push_back(rmp[a]);
    }
    for (int i = 0; i < sz; i++) {
        if (!vis[i]) bfs(i);
    }
    int ans = 0;
    for (string &i : v) ans += sm[rmp[i]];
    cout << ans;
}