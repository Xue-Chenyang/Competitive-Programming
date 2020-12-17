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

vector<vector<int>> adj;

int dfs(int u, int par, int r, vector<int>& vis, vector<int>& root, int& ecnt) {
    root[u] = r;
    vis[u] = 1;
    ecnt += adj[u].size();
    int s = 1;
    for (int child : adj[u]) {
        if (vis[child]) continue;
        s += dfs(child, u, r, vis, root, ecnt);
    }
    return s;
}

typedef pair<int, int> ii;

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        adj.assign(n, vector<int>());
        for (int i = 0; i < n - 1; i++) {
            int a, b; cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<ii> values(n);
        for (int i = 0; i < n; i++) {
            cin >> values[i].first;
            values[i].second = i;
        }
        vector<int> vis(n, 0), root(n), ssize(n), ecnts(n);
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            ssize[i] = dfs(i, i, i, vis, root, ecnts[i]);
            if (ssize[i] < ecnts[i] / 2) {
                cout << "impossible" << endl; flag = false;
                break;
            }
        }
        if (!flag) continue;
        sort(values.begin(), values.end(), [](ii& p, ii& q) {
            if (p.first == q.first) return p.second < q.second;
            return p.first > q.first;
        });
        ii fir = { -1,-1 }, sec = { -1,-1 }, cir = { -1,-1 };
        for (int i = 0; i < n; i++) {
            if (ssize[root[values[i].second]] == 1) {
                if (values[i].second == 0) {
                    cout << "1 2" << endl;
                    flag = false;
                    break;
                }
                else {
                    cout << "1 " << values[i].second + 1 << endl;
                    flag = false;
                    break;
                }
            }
            if (ssize[root[values[i].second]] * 2 == ecnts[root[values[i].second]]) {
                if (cir.first < 0 || cir.second > values[i].second) {
                    cir = values[i];
                }
                continue;
            }
            if (fir.first < 0) {
                fir = values[i];
            }
            else {
                if (sec.first < 0) sec = values[i];
            }
        }
        if (!flag) continue;
        if (sec.first < fir.first) {
            if (cir.first >= 0) {
                sec = cir;
            }
        }
        else {
            if (cir.first >= 0 && cir.second < sec.second) {
                sec = cir;
            }
        }
        int A = fir.second + 1, B = sec.second + 1;
        if (A > B) swap(A, B);
        cout << A << " " << B << endl;
    }
}