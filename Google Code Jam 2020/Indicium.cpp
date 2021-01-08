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

int n, tc, tr;
int M[50][50];

int aug(int v, vi & mat, vi&vis,vector<vi> & adj) {
	if (vis[v]) return 0;
	vis[v] = 1;
	for (int r : adj[v]) {
		if (mat[r] == -1 || aug(mat[r], mat, vis, adj)) {
			mat[r] = v;
			return 1;
		}
	}
	return 0;
}

void match(int ind) {
	vector<vector<int>> adj(n);
	for (int i = 0; i < n; i++) {
		if (M[ind][i] > 0) {
			adj[i].push_back(M[ind][i]);
			continue;
		}
		vector<int> freq(n + 1, 0);
		for (int j = 0; j < ind; j++) {
			freq[M[j][i]] ++;
		}
		for (int j = 0; j < n; j++) {
			if (M[ind][j] > 0) {
				freq[M[ind][j]] ++;
			}
		}
		for (int c = 1; c <= n; c++) {
			if (freq[c] == 0) {
				adj[i].push_back(c);
			}
		}
	}
	vi mat(n + 1, -1);
	unordered_set<int> freeL;
	for (int i = 0; i < n; i++) {
		freeL.insert(i);
	}
	for (int i = 0; i < n; i++) {
		vi candidate;
		for (int c : adj[i]) {
			if (mat[c] < 0) {
				candidate.push_back(c);
			}
		}
		if (!candidate.empty()) {
			int a = rand() % candidate.size();
			mat[candidate[a]] = i;
			freeL.erase(i);
		}
	}
	for (int v : freeL) {
		vi vis(n + 1, 0);
		aug(v, mat, vis, adj);
	}
	for (int i = 1; i <= n; i++) {
		M[ind][mat[i]] = i;
	}
}

int main() {
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		cin >> n >> tr;
		cout << "Case #" << _ << ": ";
		if (n == 2) {
			if (tr == 2) {
				cout << "POSSIBLE\n1 2\n2 1\n";
				continue;
			}
			if (tr == 3) {
				cout << "IMPOSSIBLE\n";
				continue;
			}
			if (tr == 4) {
				cout << "POSSIBLE\n2 1\n1 2\n";
				continue;
			}
			continue;
		}
		if (n == 3) {
			if (tr == 3) {
				cout << "POSSIBLE\n1 2 3\n3 1 2\n2 3 1\n";
				continue;
			}
			if (tr == 6) {
				cout << "POSSIBLE\n2 1 3\n3 2 1\n1 3 2\n";
				continue;
			}
			if (tr == 9) {
				cout << "POSSIBLE\n3 2 1\n1 3 2\n2 1 3\n";
				continue;
			}
			cout << "IMPOSSIBLE\n";
			continue;
		}
		if (tr == n + 1 || tr == n * n - 1) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		int a, b, c;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					if ((i == j && j != k) || (i == k && j != k)) continue;
					if (i * (n - 2) + j + k == tr) {
						a = i; b = j; c = k;
						goto Solve;
					}
				}
			}
		}
	Solve: ms(M, 0);
		for (int i = 2; i < n; i++) {
			M[i][i] = a;
		}
		M[0][0] = b; M[1][1] = c; 
		if (b != a || c != a) {
			M[0][1] = a; M[1][0] = a;
		}
		for (int i = 0; i < n; i++) {
			match(i);
		}
		cout << "POSSIBLE\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << M[i][j];
				if (j == n - 1) {
					cout << endl;
				}
				else {
					cout << " ";
				}
			}
		}
	}
}