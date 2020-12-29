#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
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

typedef long long ll;

const ll MOD = 998244353;

int n, m;
vector<vector<int>> adj;
vector<int> sg, vis, freq;
ll mat[1000][1000], inv[1000][1000];

ll modpow(ll m, ll p) {
    if (p == 0) return 1;
    ll ans = modpow(m, p / 2);
    ans = (ans * ans) % MOD;
    if (p & 1) ans = (ans * m) % MOD;
    return ans;
}

ll minv(int p) {
    return modpow(p, MOD - 2);
}

void dfs(int u) {
    vis[u] = 1;
    vector<int> buf;
    for (int c : adj[u]) {
        if (vis[c]<0) dfs(c);
        buf.push_back(sg[c]);
    }
    int cur = 0;
    sort(buf.begin(), buf.end());
    for (int i = 0; i < buf.size(); i++) {
        if (cur == buf[i]) cur++;
    }
    sg[u] = cur;
    freq[cur] ++;
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    sg.resize(n + 1);
    freq.assign(2000, 0);
    vis.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (vis[i] > 0) continue;
        dfs(i);
    }
    memset(mat, 0, sizeof mat);
    memset(inv, 0, sizeof inv);
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            if (i == j) {
                mat[i][j] = n + 1;
                inv[i][j] = 1;
            }
            mat[i][j] = (MOD + mat[i][j] - freq[i ^ j]) % MOD;
        }
    }
    for (int col = 0; col < 512; col++) {
        //cout << col << endl;
        for (int row = col; row < 512; row++) {
            if (mat[row][col] == 0) continue;
            for (int k = 1; k < 512; k++) {
                swap(mat[col][k], mat[row][k]);
                swap(inv[col][k], inv[row][k]);
            }
            break;
        }
        ll mul = minv(mat[col][col]);
        for (int k = 0; k < 512; k++) {
            mat[col][k] = ((mat[col][k]) * mul) % MOD;
            inv[col][k] = ((inv[col][k]) * mul) % MOD;
        }
        for (int row = 0; row < 512; row++) {
            if (row == col) continue;
            mul = (MOD - mat[row][col]) % MOD;
            for (int k = 0; k < 512; k++) {
                mat[row][k] = (mat[row][k] + mul * mat[col][k]) % MOD;
                inv[row][k] = (inv[row][k] + mul * inv[col][k]) % MOD;
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i < 512; i++) {
        ans = (ans + inv[0][i]) % MOD;
    }
    cout << ans << endl;
}