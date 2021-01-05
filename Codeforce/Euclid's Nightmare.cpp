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
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<int> vi;

const ll MOD = 1e9 + 7;

ll modpow(ll m, int p) {
	if (p == 0) return 1;
	ll ans = modpow(m, p / 2);
	ans = (ans * ans) % MOD;
	if (p & 1) {
		ans = (ans * m) % MOD;
	}
	return ans;
}

int n, m;
vector<pair<int, int>> rec;
vector<int> ans;
vector<bool> solid;
vector<vector<int>> adj;
vector<int> parent;

void solidify(int u, int p) {
	if (solid[u]) return;
	solid[u] = true;
	for (int c : adj[u]) {
		if (c == p) continue;
		solidify(c, u);
	}
	adj[u].clear();
}

int get_root(int u) {
	if (parent[u] == u) {
		return u;
	}
	int p = get_root(parent[parent[u]]);
	parent[u] = p;
	return p;
}

void uni(int a, int b) {
	int ar = get_root(a), br = get_root(b);
	parent[ar] = br;
}

int main(){
	cin >> n >> m;
	solid.assign(m + 1, false);
	adj.assign(m + 1, vi());
	parent.resize(m + 1);
	for (int i = 0; i < m + 1; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		int a, b; 
		if (k == 1) {
			cin >> a;
			if (solid[a]) {
				continue;
			}
			solidify(a, a);
			ans.push_back(i);
		}
		else {
			cin >> a >> b;
			if (solid[a]) {
				if (solid[b]) {
					continue;
				}
				solidify(b, b);
				ans.push_back(i);
			}
			else {
				if (solid[b]) {
					solidify(a, a);
					ans.push_back(i);
				}
				else {
					if (get_root(a) == get_root(b)) {
						continue;
					}
					else {
						adj[a].push_back(b); adj[b].push_back(a);
						uni(a, b);
						ans.push_back(i);
					}

				}
			}
		}
	}
	cout << modpow(2, ans.size()) << " " << ans.size() << endl;
	for (int aa : ans) {
		cout << aa + 1 << " ";
	}
	cout << endl;
}
