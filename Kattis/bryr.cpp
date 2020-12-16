#include <bits/stdc++.h>
#define MAXN 100005
#define INF 100000000
using namespace std;
typedef pair<int,int> ii;
typedef vector<vector<ii>> vv;

int main() {
	int n,m; cin >> n >> m;
	vv adj(n);
	for (int i= 0; i < m; i++) {
		int u,v,w; cin >> u >> v >> w;
		u--, v--;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
    }
    deque<int> q;
    vector<int> d(n + 5, INF);
    d[0] = 0;
    q.push_back(0);
    while (!q.empty()) {
		int u = q.front();
		q.pop_front();
		for (auto &[v,w]: adj[u]) {
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				if (!w) {
					q.push_front(v);
				} else q.push_back(v);
			}
				
		}
	}
	cout << d[n - 1];
}
