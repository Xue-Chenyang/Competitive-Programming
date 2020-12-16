#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
	int child[26];
	int idx;
	int par;
	int par_c;
	
	node() {
		idx = -1;
		par = -1;
		par_c = -1;
		memset(child, -1, sizeof (child));
		
	}
	
	node(int p, int pc) {
		idx = -1;
		par_c = pc;
		par = p;
		memset(child, -1, sizeof (child));
	}
};

int trie_cnt = 0;
vector<node> trie;
vector<int> labels;
vector<vector<int>> adj;

int insstr(string s, int v, int ind) {
	if (ind >= s.length()) {
		return v;
	}
	int c = s[ind] - 'a';
	if (trie[v].child[c] < 0) {	
		trie[v].child[c] = trie_cnt;
		trie_cnt ++;
		trie.push_back(node(v, c));
	}
	return insstr(s, trie[v].child[c], ind+1);
}

int go(int v, vector<int>& suffix, int idx) {
	if (idx < 0) {
		return trie[v].idx;
	}
	if (trie[v].child[suffix[idx]] < 0) {
		return -1;
	}
	return go(trie[v].child[suffix[idx]], suffix, idx-1);
}

void process(int idx, int v, vector<int>& suffix) {
	for (int c = 0; c < 26; c ++) {
		if (trie[v].child[c] < 0) continue;
		int w = go(trie[v].child[c], suffix, suffix.size()-1);
		if (w > idx) {
			adj[idx].push_back(w);
		}
		if (!suffix.empty() && suffix.back() != c) {
			w = go(trie[v].child[c], suffix, suffix.size()-2);
			if (w > idx) {
				adj[idx].push_back(w);
			}
		}
	}
	if (!suffix.empty()) {
		int w = go(v, suffix, suffix.size()-2);
		if (w > idx) {
			adj[idx].push_back(w);
		}
	}
	if (trie[v].par >= 0) {
		suffix.push_back(trie[v].par_c);
		process(idx, trie[v].par, suffix);
	}
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	
	vector<string> wds;
	string s;
	trie.push_back(node());
	trie_cnt ++;
	labels.assign(50000, -1);
	
	int n = 0;
	
	
	while (cin >> s, !cin.eof()) {
		wds.push_back(s);
		
		labels[n] = insstr(s, 0, 0);
		//cout << labels[n] << endl;
		trie[labels[n]].idx = n;
		n ++;
	}
	
	
	/*
	cin >> n;
	//cout << n << endl;
	for (int i = 0; i < n; i ++) {
		//cout << "reading" << endl;
		cin >> s;
		//cout << s << endl;
		
		labels[i] = insstr(s, 0, 0);
		trie[labels[i]].idx = i;
	}
	*/
	//cout << "finish read" << endl;
	
	adj.assign(n, vector<int>());
	for (int i = 0; i < n; i ++) {
		vector<int> ve;
		process(i, labels[i], ve);
	}
	
	
	vector<int> dp(n, 1);
	int ans = 0;
	//cout << "graph is " << endl;
	for (int i = 0; i < n; i ++) {
		ans = max(ans, dp[i]);
		for (int j : adj[i]) {
			//cout << j << " ";
			dp[j] = max(dp[j], dp[i] + 1);
		}
		//cout << endl;
	}
	cout << ans << endl;
}
