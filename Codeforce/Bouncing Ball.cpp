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

struct pos {
    int exp;
    int addi;
    int ind;

    bool operator < (const pos& str) const
    {
        if (exp >= 20 || str.exp >= 20) {
            if (exp != str.exp) return exp > str.exp;
            return addi > str.addi;
        }
        else {
            return (1 << exp) + addi > (1 << str.exp) + str.addi;
        }
    }
};

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

class Sell_Compare {
public:
    bool operator() (string id1, string id2) {
        return true;
    }
};

#define forn(i, n) for (int i = 0; i < int(n); i++)

int tc, n, p, k, x, y;
char buf[100005];
ll cost[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    scanf("%d", &tc);
    forn(t, tc) {
        scanf("%d%d%d", &n, &p, &k);
        scanf("%s", buf);
        scanf("%d%d", &x, &y);
        ll ans = 1e12;
        for (int i = n - 1; i >= p-1; i--) {
            if (i + k >= n) {
                cost[i] = buf[i] == '0' ? x : 0;
            }
            else {
                cost[i] = cost[i + k];
                cost[i] += (buf[i] == '0' ? x : 0);
            }
            ans = min(ans, (ll)(i - p + 1) * y + cost[i]);
        }
        printf("%lld\n", ans);
    }
}