#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    ll v,cap,flow;
};

vector<edge> EL;
vector<vector<int>> adj;
vector<int> d,last;
int n,s,t;
ll total = 0;
bool bfs() {
    d.assign(n,  -1); d[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) return true;
        for (auto idx: adj[u]) {
            edge &e = EL[idx];
            if (d[e.v] == -1 && e.cap - e.flow) {
                d[e.v] = d[u] + 1;
                q.push(e.v);
            }
        }
    }
    return false;
}
ll dfs(int u, ll flow) {
    if (u == t) return flow;
    for (int &i = last[u]; i < adj[u].size(); i++) {
        edge &e = EL[adj[u][i]], &res = EL[adj[u][i]^1];
        ll remcap = e.cap - e.flow;
        if (remcap && d[e.v] == d[u] + 1) {
            ll fl = dfs(e.v, min(flow, remcap));
            if (fl) {
                e.flow += fl; res.flow -= fl;
                return fl;
            }
        }
    }
    return 0;
}

void addedge(ll u, ll v, ll cap) {
    adj[u].push_back(EL.size());
    EL.push_back({v, cap, 0});
    adj[v].push_back(EL.size());
    EL.push_back({u,0,0});
}
int fn, k, h;
int grid[100][100];
int cow[100][100] = {0};
typedef pair<int, int> ii;

vector<int> flood;
int dr[] = {1,-1,0,0 ,0};
int dc[] = {0,0,1,-1 ,0 };

int main() {
    cin>>fn>>k>>h;

    for (int i = 0; i < fn; i++) {
        for (int j = 0; j < fn; j++) {
            cin>>grid[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        int r,c; cin>>r>>c;
        cow[r][c] = 1;
    }
    for (int i = 0; i < h; i++) {
        int f; cin>>f;
        flood.push_back(f);
    }

    n = fn * fn * (h + 1) * 2 + 2;
    s = n -2; t = n -1;
    int offset = fn*fn*(h + 1);
    adj.resize(n);

    // Source to starting
    for (int i = 0; i < fn; i++) {
        for (int j = 0; j < fn; j++) {
            if (cow[i][j]) addedge(s , i * fn + j, 1);
        }
    }

    // Connect vertex to itself
    for (int i = 0; i < fn; i++) {
        for (int j = 0; j < fn; j++) {
            int val = i * fn + j;
            for (int k = 0; k <= h; k++) {
                addedge(val + k * fn * fn , val + k * fn * fn+ offset , 1);
            }
        }
    }

    // Connect vertex to neighbours
    for (int i = 0; i < fn; i++) {
        for (int j = 0; j < fn; j++) {
            int val = i * fn + j;
            for (int k = 0; k < 5; k++) {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if (nr < 0 || nr >= fn || nc < 0 || nc >= fn) continue;
                int val2 = nr * fn + nc;
                for (int l = 0; l < h; l++) {
                    int floodh = flood[l];
                    if (grid[nr][nc] > floodh) {
                        addedge(val + l*fn*fn+offset, val2 + (l+1) * fn * fn, 1e18);
                    }
                }
            }
        }
    }

    // last layer to end
    for (int i = 0; i < fn; i++) {
        for (int j = 0; j < fn; j++) {
            int val = i * fn + j;
            addedge(val + h* fn*fn + offset, t, 1);
        }
    }

    ll mf = 0, f;
    while (bfs()) {
        last.assign(n , 0);
        while (f = dfs(s,1e18)) {
            mf += f;
        }
    }
    cout<<mf;






}