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
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<ll> vi;

int main() {
    int tc; scanf("%d", &tc);
    while (tc--) {
        int n; scanf("%d", &n);
        vi values(n);
        ll ans = 0;
        forn(i, n) {
            scanf("%lld", &values[i]);
            ans += values[i];
        }
        vi d(n, 0);
        forn(i, n - 1) {
            int a, b; scanf("%d%d", &a, &b);
            a--; b--;
            d[a] ++; d[b]++;
        }
        vector<pair<ll, int>> r;
        for (int i = 0; i < n; i++) {
            r.push_back({ values[i], d[i] });
        }
        sort(r.begin(), r.end(), greater<pair<ll, int>>());
        printf("%lld", ans);
        for (pair<ll, int> p : r) {
            for (int i = 0; i < p.second - 1; i++) {
                ans += p.first;
                printf(" %lld", ans);
                
            }
        }
        printf("\n");
    }
}