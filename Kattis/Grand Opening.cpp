#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> adj;
unordered_set<string> vis;

void dfs(string u) {
	vis.insert(u);
	for (auto v: adj[u]) {
		if (!vis.count(v)) {
			dfs(v);
		}
	}
}

int main() {
	int n,m; cin>>n>>m;
	int edges = 0;
	vector<string> all;
	unordered_map<string, int> indeg;
	string st;
	for (int i = 0; i < n; i++) {
		string enc; cin>>enc;
		all.push_back(enc);
		
		if (indeg.count(enc) == 0) indeg[enc] = 0;
		int num; cin>>num;
		
		if (num) st = enc;
		for (int j = 0; j < num; j++) {
			string animal; cin>>animal;
			if (animal == enc) continue;
			edges++;
			if (indeg.count(animal) == 0) indeg[animal] = 0;
			adj[enc].push_back(animal);
			indeg[enc]--;
			indeg[animal]++;
		}
	}
	

	
	int indeg1 = 0;
	if (edges == 0) {
		cout<<"FALSE ALARM"; return 0;
	} 
	for (auto it: indeg) {
		string name;
		int cnt;
		name = it.first;
		cnt = it.second;
		if (cnt > 1 || cnt < -1) {
			cout<<"IMPOSSIBLE"; return 0;
		} else if (cnt == 1 || cnt == -1) {
			if (cnt == -1) st = name;
			indeg1++;
		}
	}
	
	dfs(st);
	for (auto it: all) {
		if (adj[it].size() == 0 || vis.count(it)) continue;
		cout<<"IMPOSSIBLE"; return 0;
	}
	
	if (indeg1 == 0 || indeg1 == 2) cout<<"POSSIBLE";
	else cout<<"IMPOSSIBLE";
}
