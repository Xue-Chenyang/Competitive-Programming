#pragma warning( disable : 4996 )
#include <bits/stdc++.h>

using namespace std;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int lsone(int l) {
    return l & (-1 * l);
}

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

#define MAXN 200005
#define INF 1e16
typedef long long ll;
typedef pair<ll, ll> ii;

struct edge {
    ll C, flow, u, v, w, rev;
};

vector<edge> e;
vector<vector<ll>> g;
ll parent[MAXN], level[MAXN], p_edge[MAXN], s, t, n;
void addEdge(ll src, ll dst, ll cap, ll cost) {
    edge e1 = { cap, 0, src, dst, cost, (ll)(g[dst].size()) };
    edge e2 = { 0, 0, dst, src, -cost, (ll)(g[src].size()) };
    g[src].push_back((ll)(e.size()));
    e.push_back(e1);
    g[dst].push_back((ll)(e.size()));
    e.push_back(e2);
}

bool bfs() {
    memset(parent, -1, sizeof(parent));
    for (long i = 0; i < n; i++) level[i] = LLONG_MAX;
    vector<bool> inq(n, false);
    level[s] = 0;
    deque<ll> q;
    q.push_front(s);
    while (!q.empty()) {
        ll u = q.front();
        q.pop_front();
        inq[u] = false;
        for (long i = 0; i < g[u].size(); i++) {
            edge& e1 = e[g[u][i]];
            if (level[e1.v] > level[u] + e1.w && e1.C > e1.flow) {
                level[e1.v] = level[u] + e1.w;
                parent[e1.v] = u;
                if (!inq[e1.v]) {
                    inq[e1.v] = true;
                    q.push_back(e1.v);
                }
                p_edge[e1.v] = i;
            }
        }
    }
    if (level[t] == LLONG_MAX) return false;
    return true;
}

ll mcmf() {
    ll res = 0, cost = 0;
    while (bfs()) {
        ll flow = LLONG_MAX;
        for (ll curr = t; curr != s; curr = parent[curr]) {
            ll pu = parent[curr]; ll pr = p_edge[curr];
            flow = min(flow, e[g[pu][pr]].C - e[g[pu][pr]].flow);
        }
        res += flow;
        for (ll curr = t; curr != s; curr = parent[curr]) {
            ll pu = parent[curr]; ll pr = p_edge[curr]; ll bc = e[g[pu][pr]].rev;
            e[g[pu][pr]].flow += flow;
            cost += e[g[pu][pr]].w * flow;
            e[g[curr][bc]].flow -= flow;
        }
    }
    return cost;
}

int main() {
    fast();
    int tc;
    cin >> tc;
    while (tc--) {
        int r, c;
        cin >> c >> r;
        n = c * r * 2 + 2;
        g.assign(n, vector<ll>());
        e.clear();
        forn(i, r) {
            string s;
            cin >> s;
            forn(j, c) {
                if (s[j] == '.') {
                    addEdge(2 * (i * c + j), 2 * (i * c + j ) + 1, 2, 0);
                }
                else if (s[j] == '*') {
                    addEdge(2 * (i * c + j), 2 * (i * c + j) + 1, 1, -1);
                    addEdge(2 * (i * c + j), 2 * (i * c + j) + 1, 1, 0);
                }
                if (j < c - 1) {
                    addEdge(2 * (i * c + j) + 1, 2 * (i * c + j + 1), 2, 0);
                }
                if (i < r - 1) {
                    addEdge(2 * (i * c + j) + 1, 2 * ((1 + i) * c + j), 2, 0);
                }
            }
        }
        s = n - 2; t = n - 1;
        addEdge(s, 0, 2, 0);
        addEdge(n - 3, t, 2, 0);
        ll ans = mcmf();
        cout << -ans << endl;
    }
    return 0;
}