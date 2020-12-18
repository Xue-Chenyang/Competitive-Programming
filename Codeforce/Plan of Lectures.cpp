#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef unordered_set<int> si;
#define forn(i,n) for (int i = 0; i < n; i ++)
vector<vi> adj, ids_rev;
vector<unordered_set<int>> f_preq, f_rev_preq;
int n, k, idcnt, viscnt;
vi preq, adj2, vis, ids, order_in_group;

bool dfs(int u, int p) {
    vis[u] = 1;
    viscnt ++;
    ids[u] = p;
    ids_rev[p].push_back(u);
    order_in_group[u] = ids_rev[p].size();
    if (adj2[u] >= 0) {
        if (vis[adj2[u]]) return false;
        dfs(adj2[u], p);
    }
    return true;
}

int main() {
    cin >> n >> k;
    adj.assign(n + 1, vi());
    preq.resize(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> preq[i];
        if (i > 0) {
            adj[preq[i]].push_back(i);
        }
    }
    adj2.assign(n+1, -1);
    vector<bool> start_grp(n+1, true);
    forn(i,k) {
        int a,b; cin >> a >> b;
        if (adj2[a] >= 0) {
            cout << 0;
            return 0;
        }
        adj2[a] = b;
        start_grp[b] = false;
    }

    vis.assign(n+1,0);
    f_preq.assign(n, si());
    f_rev_preq.assign(n, si());
    idcnt = 0;
    ids.assign(n+1, -1);
    ids_rev.assign(n, vi());
    order_in_group.assign(n+1, 0);
    viscnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (!vis[i] && start_grp[i]) {
            if (!dfs(i, idcnt)) {
                cout << 0;
                return 0;
            }
            idcnt ++;
        }
    }
    if (viscnt != n) {
        cout << 0;
        return 0;
    }
    
    vi indegrees(idcnt);
    queue<int> q;
    for (int i = 0; i < idcnt; i ++) {
        
        si s;
        for (int u : ids_rev[i]) {
            int p = preq[u];
            if (p <= 0) continue;
            if (ids[p] == i) {
                if (order_in_group[p] > order_in_group[u]) {
                    cout << 0;
                    return 0;
                }
            } else {
                s.insert(ids[p]);
                f_rev_preq[ids[p]].insert(i);
            }
        }
        f_preq[i] = s;
        indegrees[i] = s.size();
        if (indegrees[i] == 0) q.push(i);
    }

    vi ans;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int c : f_rev_preq[u]) {
            indegrees[c] --;
            if (indegrees[c] == 0) {
                q.push(c);
            }
        }
    }

    vi real_ans;
    for (int i : ans) {
        for (int j : ids_rev[i]) {
            real_ans.push_back(j);
        }
    }

    if (real_ans.size() == n) {
        for (int j = 0; j < real_ans.size(); j ++) {
            cout << real_ans[j] << " ";
        }
    } else {
        cout << 0;
    }
    return 0;
}

