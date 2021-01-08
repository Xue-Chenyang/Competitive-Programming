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

int n, tc;

vector<vi> V, alive;

int prop(vector<vi> & d, int x, int y, bool vertical) {
	if (x < 0 || y < 0) return -1;
	if (alive[x][y]) {
		if (vertical) {
			return x;
		}
		else {
			return y;
		}
	}
	if (vertical) {
		d[x][y] = prop(d, d[x][y], y, true);
		return d[x][y];
	}
	else {
		d[x][y] = prop(d, x, d[x][y], false);
		return d[x][y];
	}
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		cout << "Case #" << _ << ": ";
		int r, c; cin >> r >> c;
		V.assign(r, vi(c,0));
		alive.assign(r, vi(c, 1));
		vector<vi> up(r, vi(c,-1)), left(r, vi(c,-1)), down(r, vi(c,-1)), right(r, vi(c,-1));
		ll ans = 0, sum = 0;
		forn(i, r) {
			forn(j, c) {
				cin >> V[i][j];
				sum += V[i][j];
				if (i > 0) {
					up[i][j] = i - 1;
				}
				if (i < r - 1) {
					down[i][j] = i + 1;
				}
				if (j > 0) {
					left[i][j] = j - 1;
				}
				if (j < c - 1) {
					right[i][j] = j + 1;
				}
			}
		}
		bool ok = true;
		int it = 0; vector<pair<int, int>> updated;
		vector<vector<int>> his(r, vi(c, 0));
		while (ok) {

			it++;
			ans += sum;
			vector<pair<int, int>> toremove;
			if (it == 1) {
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++) {
						if (!alive[i][j]) continue;
						ll comp = 0, f = 0;
						if (up[i][j] >= 0) {
							comp += V[up[i][j]][j]; f++;
						}
						if (down[i][j] >= 0) {
							comp += V[down[i][j]][j]; f++;
						}
						if (left[i][j] >= 0) {
							comp += V[i][left[i][j]]; f++;
						}
						if (right[i][j] >= 0) {
							comp += V[i][right[i][j]]; f++;
						}
						if (f > 0 && comp > 1LL * V[i][j] * f) {
							toremove.push_back({ i,j });
							sum -= V[i][j];
							alive[i][j] = 0;
						}
					}
				}
			}
			else {
				for (auto [i, j] : updated) {
					if (!alive[i][j]) continue;
					ll comp = 0, f = 0;
					if (up[i][j] >= 0) {
						comp += V[up[i][j]][j]; f++;
					}
					if (down[i][j] >= 0) {
						comp += V[down[i][j]][j]; f++;
					}
					if (left[i][j] >= 0) {
						comp += V[i][left[i][j]]; f++;
					}
					if (right[i][j] >= 0) {
						comp += V[i][right[i][j]]; f++;
					}
					if (f > 0 && comp > 1LL * V[i][j] * f) {
						toremove.push_back({ i,j });
						sum -= V[i][j];
						alive[i][j] = 0;
					}
				}
			}

			if (toremove.empty()) {
				break;
			}
			updated.clear();

			for (auto [i, j] : toremove) {
				int u = prop(up, i, j, true);
				int d = prop(down, i, j, true);
				if (u >= 0) {
					down[u][j] = d;
					if (his[u][j] != it) updated.push_back({ u,j });
					his[u][j] = it;
				}
				if (d >= 0) {
					up[d][j] = u;
					if (his[d][j] != it) updated.push_back({ d,j });
					his[d][j] = it;
				}
				int l = prop(left, i, j, false);
				int r = prop(right, i, j, false);
				if (l >= 0) {
					right[i][l] = r;
					if (his[i][l] != it) updated.push_back({ i,l });
					his[i][l] = it;
				}
				if (r >= 0) {
					left[i][r] = l;
					if (his[i][r] != it)updated.push_back({ i, r });
					his[i][r] = it;
				}
			}
		}
		cout << ans << endl;
	}
}
