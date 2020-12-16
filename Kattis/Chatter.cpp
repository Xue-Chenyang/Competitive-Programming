#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
typedef pair<int,int> ii;

int d[MAXN], sz[MAXN];
int n, r,a,b,c; 
int find(int id) {
	return (d[id] < 0) ? id : d[id] = find(d[id]);
}

void join(int s1, int s2) {
	int x1 = find(s1), x2 = find(s2);
	//cout << x1 << ' ' << x2 << '\n';
	if (x1 == x2) return;
	if (x1 < x2) {
		d[x1] = x2;
		sz[x2] += sz[x1];
    } else {
		d[x2] = x1;
		sz[x1] += sz[x2];
    }
}

ii gen() {
	int x = (r * a + b) % c;
	r = x;
	x %= n;
	
	int y = (r * a + b) % c;
	r = y;
	y %= n;
	return {x,y};
}

int main() {
	while (cin >> n, !cin.eof()) {
		memset(d, -1, sizeof(d));
		for (int i = 0; i < n; i++) sz[i] = 1;
		cin >> r >> a >> b >> c;
		for (int iter = 0; iter < n; iter++) {
			ii p = gen();
			while (p.first == p.second) p = gen();
			//cout << p.first << ' ' << p.second << '\n';
			join(p.first, p.second);
		}
		unordered_map<int,int> m;
		unordered_set<int> s;
		for (int i = 0; i < n; i++) s.insert(find(i));
		vector<ii> v;
		for (auto &i : s) m[sz[i]]++;
		for (auto &[key,val] : m) v.push_back({key,val});
		sort(v.begin(), v.end());
		int ans = 0;
		//cout << v.size() << '\n';
		for (int i = v.size() - 1; i >= 0; i--) {
			ans += v[i].second;
		}
		cout << ans << ' ';
		for (int i = v.size() - 1; i >= 0; i--) {
			cout << v[i].first;
			if (v[i].second > 1) cout << "x" << v[i].second;
			cout << ' ';
		}
		cout << '\n';
	}
	
}
