#include <bits/stdc++.h>
using namespace std;

int main() {
	char mc; cin >> mc;
	int mamt = mc - 'a';
	int n; cin >> n;
	vector<string> v(n);
	vector<int> indeg(30, 0);
	for (string &i : v) cin >> i;
	vector<vector<int>> adj(30);
	bool ac = true;
	for (int i = 0; i < n && ac; i++) {
		for (int j = i + 1; j < n && ac; j++) {
			int len = min(v[i].length(), v[j].length()), k;
			for (k = 0; k < len; k++) {
				if (v[i][k] != v[j][k]) break;
		    }
		    //cout << k << '\n';
		    if (k == len && v[i].length() > v[j].length()) {
				ac= false; 
		    } else if (k < len) {
				//cout << "enter" << '\n';
				adj[v[i][k] - 'a'].push_back(v[j][k] - 'a');
				indeg[v[j][k] - 'a']++;
			}
				
		 }
	}
	if (!ac) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	vector<int> d(30, 0);
	queue<int> q;
	vector<int> ord;
	for (int i = 0; i <= mamt; i++) {
		if (indeg[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ord.push_back(u);
		for (int &i :adj[u]) {
			d[i] = max(d[u] + 1, d[i]);
			if (--indeg[i] == 0) {
				q.push(i);
		    }
		}
	}
	if ((int)(ord.size()) != mamt + 1) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	//for (int i = 0; i <= mamt; i++) cout << d[i] << ' ';
	//cout << '\n';
	for (int i = 0; i <= mamt; i++) {
		for (int j = 0; j <= mamt; j++) {
			if (d[i] == d[j] && i != j) {
				cout << "AMBIGUOUS";
				return 0;
			}
		}
	}
	for (int &i : ord) cout << (char)(97 + i);
	
}
