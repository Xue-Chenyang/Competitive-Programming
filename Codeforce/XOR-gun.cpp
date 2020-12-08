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

int n, B[100005];
ll A[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    scanf("%d", &n);
    forn(i, n) {
        scanf("%lld", &A[i]);
        ll l = A[i];
        while (l > 0) {
            B[i] ++;
            l >>= 1;
        }
        if (i >= 2 && B[i] == B[i - 1] && B[i] == B[i - 2]) {
            printf("1\n");
            return 0;
        }
    }
    int ans = n + 100;
    for (int i = 0; i < n - 1; i++) {
        ll left = 0;
        for (int j = i; j >= 0; j--) {
            left = left ^ A[j];
            ll right = 0;
            for (int k = i + 1; k < n; k++) {
                right = right ^ A[k];
                if (right < left) {
                    ans = min(ans, k - j - 1);
                    break;
                }
            }
        }
    }
    if (ans > n) {
        printf("-1\n");
    }
    else {
        printf("%d\n", ans);
    }
}