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

int n, k, A[500005];

int main() {
    scanf("%d%d", &n, &k);
    forn(i, n) {
        scanf("%d", &A[i]);
    }
    sort(A, A + n);
    ll s = 0; int c = -1;
    for (int i = n - 1; i >= 0; i--) {
        s += A[i];
        if (s < 0) {
            c = i;
            break;
        }
    }
    int h = (c + 1) / (k + 1);
    ll ans = 0;
    for (int i = 0; i <= c; i++) {
        ans += (ll)A[i] * (i / (k + 1));
    }
    int off = c < 0 ? -1 : c / (k + 1);
    for (int i = c + 1; i < n; i++) {
        ans += (ll)A[i] * (i - c + off);
    }
    printf("%lld\n", ans);
}