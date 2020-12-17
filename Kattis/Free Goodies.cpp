#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int main() {
    int tc; cin >> tc;
    while (tc --) {
        int n; cin >> n;
        string s; cin >> s;
        ii dp[n+1][n+1];
        for (int i = 0; i <= n; i ++) {
            for (int j = 0; j <= n; j ++) {
                dp[i][j] = {-10000000,-10000000};
            }
        }
        dp[0][0] = {0,0};
        vector<ii> goodies(n);
        for (int i = 0; i < n; i ++) {
            cin >> goodies[i].first >> goodies[i].second;
        }
        sort(goodies.begin(), goodies.end(), [](ii &p, ii &q) {
            if (p.first == q.first) return p.second < q.second;
            return p.first > q.first;
        });
        int petra = 0, jan = 0, st = 0;
        if (s == "Petra") {
            petra += goodies[0].first;
            st ++;
        }
        for (int i = st + 1; i <= n; i ++) {
            for (int j = (i - st) / 2; j <= min(i - st, (n-st)/2); j ++) {
                dp[i - st][j] = {dp[i - st -1][j].first + goodies[i-1].second, dp[i-st-1][j].second};
                if (j > 0) {
                    if (ii{dp[i-st-1][j-1].first, dp[i-st-1][j-1].second + goodies[i-1].first} > dp[i-st][j]) {
                        dp[i-st][j] = {dp[i-st-1][j-1].first, dp[i-st-1][j-1].second + goodies[i-1].first};
                    }
                }
            }
        }
        petra += dp[n-st][(n-st)/2].second;
        jan += dp[n-st][(n-st)/2].first;
        cout << petra << " " << jan << endl;
    }

}