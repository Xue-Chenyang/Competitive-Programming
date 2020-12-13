#pragma warning( disable : 4996 )
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

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
#include <bits/stdc++.h>

typedef long long ll;

int ans, weight[200005], ex[200005];
vector<vi> adj;

void dfs(int v, int m) {
    ans = min(ans, m);
    for (int child : adj[v]) {
        if (weight[child] >= m) {
            dfs(child, weight[child] - ex[child]);
        }
        else {
            dfs(child, m - ex[child]);
        }
    }
}

int main() {
    fast();
    int n, w; cin >> n >> w;
    ans = w;
    adj.assign(n + 1, vi());
    for (int i = 1; i <= n; i++) {
        int p; cin >> p >> weight[i] >> ex[i];
        adj[p].push_back(i);
    }
    dfs(0, w);
    cout << ans << endl;
    return 0;
}