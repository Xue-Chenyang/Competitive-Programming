#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
using namespace std;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int lsone(int l) {
    return l & (-1 * l);
}

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;

int x, y; ll N;
vector<vector<ll>> dp(2, vector<ll>(1 << 22, -1));
int leftshift(int a) {
    return (a << 1) & ((1 << 22) - 1);
}
int main(){
    cin >> N >> x >> y;
    //ms(dp, -1);
    int p = x + y, r = N % (x + y);
    dp[0][0] = 0;
    dp[0][1] = r == 0 ? N / p : N / p + 1;
    ll ans = -1;
    for (int i = 0; i < p; i++) {
        for (int mask = 0; mask < (1 << 22); mask++) {
            if (i == p - 1) {
                ans = max(ans, dp[i & 1][mask]);
                continue;
            }
            if (dp[i & 1][mask] < 0) continue;
            int next = leftshift(mask);
            dp[(i + 1) & 1][next] = max(dp[(i + 1) & 1][next], dp[i & 1][mask]);
            if (!((mask & (1 << (x - 1))) || (mask & (1 << (y - 1))))) {
                dp[(i + 1) & 1][next + 1] = max(dp[(i + 1) & 1][next], dp[i & 1][mask] + (i + 1 < r ? N / p + 1 : N / p));
            }
        }
        dp[i & 1].assign(1 << 22, -1);
    }
    cout << ans << endl;
}