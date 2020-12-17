#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

bool vis[MAXN];
int isMatch[MAXN];
vector<set<int>> adj;
int a[MAXN][MAXN], n, k;
bool dfs(int u) {
    for (auto &i : adj[u]) {
        if (!vis[i]) {
            vis[i] = true;
            if (isMatch[i] == -1 || dfs(isMatch[i])) {
                isMatch[i] = u;
                return true;
            }
        }
    }
    return false;
}

void mcbm(int rid) {
    for (int i = 0; i < n; i++) isMatch[i] = -1;
    for (int i = 0; i < n; i++) {
        memset(vis, false, sizeof(vis)), dfs(i);
    }
    for (int i = 0 ; i < n; i++) {
        //cout << isMatch[i] << ' ';
        a[rid][isMatch[i]] = i + 1;
        adj[isMatch[i]].erase(i);
    }
    //cout << '\n';
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i].insert(j);
        }
    }
    bool ac = true;
    for (int i = 0; i < k; i++) {
        unordered_set<int> s;
        for (int j = 0; j < n; j++) {
            if (s.count(a[i][j])) {
                ac = false;
                break;
            }
            s.insert(a[i][j]);
        }
        if (!ac) break;
    } 
    if (!ac) {
        cout << "no";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        unordered_set<int> s;
        for (int j = 0; j < k; j++) {
            if (s.count(a[j][i])) {
                ac = false;
                break;
            }
            s.insert(a[j][i]);
            adj[i].erase(a[j][i] - 1);
        }
        if (!ac) break;
    } 

    if (!ac) {
        cout << "no";
        return 0;
    }
    /*
    for (int i = 0; i < n; i++) {
        for (auto &v : adj[i]) cout << v << ' ';
        cout << '\n';
    }
    */
    for (int i = k; i < n; i++) mcbm(i);
    cout << "yes" << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << ' ';
        cout << '\n';
    }
}

