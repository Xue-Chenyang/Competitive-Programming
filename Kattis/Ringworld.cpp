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

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        vector<pair<ll, ll>> segs;
        for (int i = 0; i < m; i++) {
            ll a, b;
            cin >> a >> b;
            if (a <= b) {
                segs.push_back({ b,a });
                segs.push_back({ b + n, a + n });
            }
            else {
                segs.push_back({ b + n, a });
            }
        }
        if (n < m) {
            cout << "NO\n";
            continue;
        }
        sort(segs.begin(), segs.end());
        unordered_set<ll> s; bool ok = true;
        for (int i = 0; i < segs.size(); i++) {
            bool ook = false;
            for (ll j = segs[i].second; j <= segs[i].first; j++) {
                if (!s.count(j)) {
                    s.insert(j);
                    ook = true;
                    break;
                }
            }
            if (!ook) {
                ok = false; break;
            }
        }
        if (!ok) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
}