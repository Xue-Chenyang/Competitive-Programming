#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
using namespace std;

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<int> vi;

const int MAXN = 200000; // The length of original array

const int INF = 1e9;

int A[MAXN], st[MAXN * 4], lazy[MAXN * 4], n; // A is the oriiginal data, n is the actual size of data

void build(int p, int l, int r) {

	lazy[p] = -1;
	if (l == r) {
		st[p] = A[l];
		return;
	}
	build(p << 1, l, (l + r) / 2);
	build((p << 1) + 1, (l + r) / 2 + 1, r);
	st[p] = st[p << 1] + st[(p << 1) + 1];
}

void build() {
	build(1, 0, n - 1);
}

void push_down(int p, int l, int r) { // implementation depends on what update and query means, here is the version for range increment/decrement update and range minimum query
	if (lazy[p] < 0) return;
	st[p] = (l - r + 1) * lazy[p];
	if (l != r) {
		lazy[p << 1] = lazy[p];
		lazy[(p << 1) + 1] = lazy[p];
	}
	lazy[p] = -1;
}

void update(int delta, int p, int l, int r, int ql, int qr) {
	push_down(p, l, r);
	if (ql > r || qr < l) return;
	if (l >= ql && r <= qr) {
		lazy[p] = delta;
		push_down(p, l, r);
	}
	else {
		int mid = (l + r) / 2;
		update(delta, p << 1, l, mid, ql, qr);
		update(delta, (p << 1) + 1, mid + 1, r, ql, qr);
		st[p] = st[p << 1] + st[(p << 1) + 1]; // This depends on what update means
	}
}

void update(int delta, int l, int r) { // range update of delta from left to right inclusive
	if (l > r) return;
	update(delta, 1, 0, n - 1, l, r);
}

int query(int p, int l, int r, int ql, int qr) {
	push_down(p, l, r);
	if (l >= ql && r <= qr) {
		return st[p];
	}
	int mid = (l + r) / 2;
	int ans = 0;
	if (ql <= mid) {
		ans += query(p << 1, l, mid, ql, qr);
	}
	if (qr > mid) {
		ans += (query((p << 1) + 1, mid + 1, r, ql, qr));
	}
	return ans;
}

int query(int l, int r) {
	return query(1, 0, n - 1, l, r);
}

const ll MOD = 1e9 + 7;

vector<int> color_cnt, seen;

vector<int> v, parent, tin, tout;
vector<vi> adj;
int t = -1;
void dfs(int u, int p) {
	t++;  tin[u] = t;
	bool good = true;
	if (seen[v[u]] > 0) {
		good = false;
	}
	seen[v[u]] ++;

	int rec = seen[v[u]];
	int divine = -1;
	for (int c : adj[u]) {
		if (c == p) continue;
		dfs(c, u);
		if (seen[v[u]] != rec) {
			if (divine < 0) {
				divine = c;
			}
			else {
				divine = INF;
			}
			rec = seen[v[u]];
		}
	}
	tout[u] = t;
	if (seen[v[u]] != color_cnt[v[u]]) good = false;
	if (!good && divine >= 0) {
		update(0, 0, n - 1);
		return;
	}
	if (!good) {
		update(0, tin[u], tout[u]);
	}
	if (divine >= 0) {
		update(0, 0, tin[u]);
		update(0, tout[u] + 1, n - 1);
		for (int c : adj[u]) {
			if (c == p) continue;
			if (c == divine) continue;
			update(0, tin[c], tout[c]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	unordered_map<int, int> mapping;
	v.assign(n,0);
	tin.resize(n);
	tout.resize(n);
	parent.assign(n, -1);
	color_cnt.assign(n + 1, 0);
	int cnt = 1;
	adj.assign(n, vi());
	forn(i, n) {
		int l; cin >> l;
		if (mapping.count(l)) {
			v[i] = mapping[l];
		}
		else {
			mapping[l] = cnt;
			v[i] = cnt;
			cnt++;
		}
		color_cnt[v[i]] ++;
		A[i] = 1;
	}
	for (int i = 0; i < n - 1; i++) {
		int p, q; cin >> p >> q;
		p--; q--;
		adj[p].push_back(q);
		adj[q].push_back(p);
	}
	build();
	seen.assign(n + 1, 0);
	dfs(0, 0);
	cout << query(0, n - 1) << endl;
}

