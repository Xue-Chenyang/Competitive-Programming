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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> B(m+2);
		B[0] = { 0,0 };
		forn(i, m) {
			cin >> B[i+1].second >> B[i+1].first;
			B[i + 1].first--;
		}
		B[m + 1] = { n - 1,3 };
		sort(B.begin(), B.end());
		B[m + 1].second = 0;
		for (int i = 2; i <= m; i++) {
			if (B[i].first == B[i - 1].first) {
				B[i - 1] = { B[i - 1].first, 3 };
				B[i] = { -1,-1 };
			}
		}
		int prev = 0;
		for (int i = 1; i <= m + 1; i++) {
			if (B[i].first < 0) continue;
			if (B[i].first - B[prev].first > 2) {
				if ((B[i].first - B[prev].first) % 2 == 0) {
					B[i].first = B[prev].first + 2;
				}
				else {
					B[i].first = B[prev].first + 1;
				}
			}
			prev = i;
		}
		vi A;
		A.assign(B.back().first + 1, 0);
		for (int i = 1; i <= m; i ++) {
			if (B[i].first < 0) continue;
			A[B[i].first] = B[i].second;
		}
		n = A.size();
		vector<vector<bool>> dp(n + 1, vector<bool>(3, false)), res(n + 1, vector<bool>(3, false));
		dp[0][0] = true;
		for (int i = 0; i < n; i++) {
			switch (A[i]) {
			case 0:
				res[i][0] = res[i][0] || dp[i][0];
				res[i][1] = res[i][1] || dp[i][1];
				res[i][2] = res[i][2] || dp[i][2];
				break;
			
			case 1:
				if (i + 1 <= n) dp[i + 1][0] = dp[i + 1][0] || dp[i][2];
				res[i][1] = res[i][1] || dp[i][0];
				break;

			case 2:
				if (i + 1 <= n) dp[i + 1][0] = dp[i + 1][0] || dp[i][1];
				res[i][2] = res[i][2] || dp[i][0];
				break;

			case 3:
				if (i + 1 <= n) dp[i + 1][0] = dp[i + 1][0] || dp[i][0];
				break;
			}
			for (int j = 0; j < 3; j++) {
				if (!res[i][j]) continue;
				switch (j) {
				case 0:
					if (i + 1 <= n) {
						dp[i + 1][0] = true;
					}
					break;

				case 1:
					if (i + 1 <= n) {
						dp[i + 1][2] = true;
					}
					break;
				
				case 2:
					if (i + 1 <= n) {
						dp[i + 1][1] = true;
					}
				}
			}
		}
		if (dp[n][0]) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}