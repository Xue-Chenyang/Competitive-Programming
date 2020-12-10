#pragma warning( disable : 4996 )
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

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

int n;
ll t[5005], d[5005], mini[5005];
bool dp[5005][5005];

int main() {
    scanf("%d", &n);
    ms(dp, false);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &t[i], &d[i]);
        mini[i] = 1e15;
    }
    mini[0] = 0;
    for (int i = 0; i < n; i++) {
        if (mini[i] <= t[i] || i == 0) {
            mini[i + 1] = min(mini[i + 1], max(mini[i] + abs(d[i + 1] - d[i]), t[i]));
            for (int j = i + 2; j <= n; j++) {
                if (max(t[i], mini[i] + abs(d[i] - d[j])) + abs(d[j] - d[i + 1]) <= t[i + 1]) {
                    dp[i + 1][j] = true;
                }
            }
        }
        for (int j = i + 1; j <= n; j++) {
            if (dp[i][j]) {
                if (j == i + 1) {
                    if (j < n) {
                        mini[j + 1] = min(mini[j + 1], max(t[j], t[i] + abs(d[i] - d[j + 1])));
                        for (int k = j + 2; k <= n; k++) {
                            if (max(t[j], t[i] + abs(d[i] - d[k])) + abs(d[k] - d[j + 1]) <= t[j + 1]) {
                                dp[j + 1][k] = true;
                            }
                        }
                    }
                }
                else {
                    if (t[i] + abs(d[i] - d[i + 1]) <= t[i + 1]) {
                        dp[i + 1][j] = true;
                    }
                }
            }
        }
    }
    if (mini[n] <= t[n] || dp[n - 1][n]) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}