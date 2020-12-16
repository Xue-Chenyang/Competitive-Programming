#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
struct edge{
	ll v,cap, flow;
};
ll totalppl = 0;
vector<edge> EL;
vector<vector<int>> adj;
vector<int> d, last;
int n, s, t;
int loc, shel,roads;
vector<ll> ppl;
vector<vector<pair<ll,ll>>> inputadj;
vector<pair<ll,ll>> shelters;
ll total = 0;

bool bfs() {
	
	//cout << "in bfs " << n << endl;
	d.assign(n, -1);
	d[s] = 0;
	queue<int> q; q.push(s);
	//cout << "in bfs" << endl;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u==t) return true;
		for (auto idx : adj[u]) {
			edge &e = EL[idx];
			if (d[e.v] == -1 && e.cap-e.flow) {
				d[e.v] = d[u] + 1;
				q.push(e.v);
			}
		}
	}
	return false;
}

ll dfs(int u, ll flow) {
	if (u == t) return flow;
	for (int &i = last[u]; i < adj[u].size(); i ++) {
		edge &e = EL[adj[u][i]], &res = EL[adj[u][i]^1];
		ll remcap = e.cap-e.flow;
		if (remcap && d[e.v] == d[u] + 1) {
			ll fl = dfs(e.v, min(flow, remcap));
			if (fl) {
				e.flow += fl; res.flow-= fl;
				return fl;
			}
		}
	}
	return 0;
}

void addedge(ll u, ll v, ll cap) {
	adj[u].push_back(EL.size());
	EL.push_back({v,cap,0});
	adj[v].push_back(EL.size());
	EL.push_back({u,0,0});
	
}

vector<vector<ll>> sheldist;

bool check(ll tim) {
	//cout << "check for " << tim << endl;
	vector<ll> virtualcap(1 << shel , 0);
	for (int i = 0; i < loc; i++) {
		int mask = 0;
		for (int j = 0; j < shel; j++) {
			if (sheldist[j][i] <= tim) {
				mask |= (int)(1 << j);
			}
		}
		virtualcap[mask] += ppl[i];
	}
	
	//cout << "virt complete" << endl;

	adj.clear();

	n = (1 << shel) + shel + 2;

	s = n - 2; t = n - 1;
	adj.resize(n);
	EL.clear();
	for (int i = 0; i < (1 << shel); i++) {
		addedge(s, i, virtualcap[i]);
		for (int j = 0; j < shel; j++) {
			if (i & (1 << j)) {
				addedge(i , (1<< shel) + j , 1e18);
			}
		}
	} 
	
	for (int i = 0; i < shel ; i++) {
		addedge((1 << shel) + i, t ,  shelters[i].second);
	}
	
	//cout << "before bfs" << endl;
	
	ll mf = 0, f;
	while( bfs()) {
		//cout << "in while in check" << endl;
		
		last.assign(n,0);
		while (f = dfs(s,1e18)) {
			mf += f;
		}
	}
	return mf == totalppl;
}


int main() {
	
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	//cout.tie(NULL);
	
	cin>>loc>>roads>>shel;
	ppl.resize(loc);
	inputadj.resize(loc);
	shelters.resize(shel);
	for (int i = 0; i < loc; i++) {
		ll num ; cin>>num;
		totalppl += num;
		ppl[i] = num;
	}
	for (int i = 0; i < roads; i++) {
		int u,v,w; cin>>u>>v>>w; u--; v--;
		inputadj[u].push_back({v,w});
		inputadj[v].push_back({u,w});
	}
	for (int i = 0; i < shel; i++) {
		int si, ci; cin>>si>>ci; si--;
		shelters[i] = {si,ci};
	}
	
	//cout << "!!" << endl;
	
	sheldist.resize(shel);
	ll max_dist = 0;
	for (int i = 0; i < shel; i++) {
		int st = shelters[i].first;
		
		priority_queue<pll, vector<pll>, greater<pll>> pq;
		vector<ll> dist(loc, 1e15);
		dist[st] = 0;
		pq.push({0,st});
		while (!pq.empty()) {
			ll u , d; tie(d, u) = pq.top(); pq.pop();
			if (dist[u] < d) continue;
			for (auto it: inputadj[u]) {
				ll v,w; tie(v,w) = it;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.push({dist[v] , v});
				}
			}
		}
		sheldist[i].resize(loc);
		for (int j = 0; j < loc; j++) {
			sheldist[i][j] = dist[j];
			max_dist = max(max_dist, dist[j]);
		}
	}
	
	//cout << "???" << endl;
	
	ll left = 0, right = 1e15, ans = -1;
	while (left <= right) {
		ll mid = (left + right) / 2;
		if (check(mid)) {
			right = mid - 1;
			ans = mid;
		} else {
			left = mid + 1;
		}
	}
	
	cout << ans << endl;
	

}
