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

/**
void getAns(int u, vector<vector<int>>& adj, vi & A, vi & B, bool isA = true) {
	if (isA) {
		if (A[u] >= 0) {
			return;
		}
		for (int c : adj[u]) {

		}
	}
}


int main() {
	int tc; scanf("%d", &tc);
	while (tc--) {
		int n, m;
		scanf("%d%d", &n, &m);
		vector<vector<int>> adj(n, vi());
		for (int i = 0; i < n; i++) {
			int a, b; scanf("%d%d", &a, &b);
			a--; b--;
			adj[a].push_back(b);
		}
		vi d(n,-1);
		queue<int> q; q.push(0); d[0] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int c : adj[u]) {
				if (d[c] == -1) {
					d[c] = d[u] + 1;
					q.push(c);
				}
			}
		}
		vector<int> A(n,-1), B(n,-1);
		for (int i = 0; i < n; i++) {
			getAns(i, adj, A, B);
		}
	}
}
*/

vi A, B;
int n, k, t;

void prepare() {
	A.assign(n+1, k);
	t = rand() % n;
	//cin >> t;
	cout << "Imposter is " << t + 1 << endl;
}

int answer(int q) {

	B.assign(n + 1, 0);
	int a = A[q];
	for (int i = 0; i < n; i++) {
		//cout << A[i] << " ";
		if (i == t) {
			B[(i + 1) % n] += A[i];
		}
		else {
			B[(i - 1 + n) % n] += A[i] / 2;
			B[(i + 1) % n] += (A[i] + 1) / 2;
		}
	}
	bool b = false;
	for (int i = 0; i < n; i++) {
		if (A[i] != B[i]) b = true;
		A[i] = B[i];
	}
	//cout << endl;
	return a;
	//cout << endl;
}

int query(int ind) {
	cout << "? " << ind + 1 << endl;
	//int a = answer(ind);
	//cout << a << endl;
	//return a;
	int a; cin >> a;
	
	return a;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	cin >> n >> k;
	//prepare();

	int cur = 0;
	int round = 0;
	while (true) {
		int res = query(cur);
		if (res < k) {
			int left = cur, right = (cur + 2 * round) % n;
			if (2 * round >= n) {
				right = (left + n - 1) % n;
			}
			while (left != right) {
				int rr = right < left ? right + n : right;
				int mid = ((left + rr) / 2) % n;
				res = query(mid);
				if (res < k) {
					left = (mid + 1) % n;
				}
				else {
					right = mid;
				}
			}
			cout << "! " << left + 1 << endl;
			return 0;
		}
		if (res > k) {
			int right = cur, left = ((cur - 2 * round) % n + n) % n;
			if (2 * round >= n) {
				left = (right + 1) % n;
			}
			while (left != right) {
				int rr = right < left ? right + n : right;
				int mid = ((left + rr) / 2) % n;
				res = query(mid);
				if (res < k) {
					left = (mid + 1) % n;
				}
				else {
					right = mid;
				}
			}
			cout << "! " << left + 1 << endl;
			return 0;
		}
		int step = 277741;
		if (round < 30) {
			step = 1 << round;
		}
		cur = (cur + step) % n;
		round++;
		//cout << round << endl;
	}
}