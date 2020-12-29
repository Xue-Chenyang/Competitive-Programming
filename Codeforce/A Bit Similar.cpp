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
typedef vector<int> vi;

int cd(int a, int b) {
    int c = a / b;
    if (a % b != 0)c++;
    return c;
}

typedef pair<int, int> ii;

const ll MOD = 10000004039;

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        unordered_set<ll> f;
        ll cur = 0;
        vector<ll> offset(k+1);
        offset[0] = 1;
        for (int i = 0; i < k; i++) {
            offset[i+1] = (offset[i] * 2) % MOD;
        }
        for (int i = 0; i < n; i++) {
            int ind = s[i] == '1' ? 1 : 0;
            cur = (cur * 2 + ind) % MOD;
            if (i >= k && s[i-k] == '1') {
                cur = (cur + MOD - offset[k]) % MOD;
            }
            if (i >= k - 1) {
                f.insert(cur);
            }
        }
        vector<char> re(k, 1);
        bool flag = false, tob = false;; ll hash = 0;
        for (int i = 0; i < k; i++) {
            hash = (hash + offset[i]) % MOD;
        }
        while (!tob) {
            if (!f.count(hash)) {
                flag = true;
                break;
            }
            for (int i = k - 1; i >= 0; i--) {
                if (re[i] == 0) {
                    hash = (hash + offset[k - 1 - i]) % MOD;
                    re[i] = 1;
                }
                else {
                    hash = (hash + MOD - offset[k - 1 - i]) % MOD;
                    re[i] = 0;
                    break;
                }
                if (i == 0) {
                    tob = true;
                }
            }
        }
        if (flag) {
            printf("YES\n");
            for (char c : re) {
                printf("%c", (char)(1 - c + '0'));
            }
            printf("\n");
        }
        else {
            printf("NO\n");
        }
    }
}