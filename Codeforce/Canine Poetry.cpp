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

int main() {
    int tc; scanf("%d", &tc);
    while (tc--) {
        string s; cin >> s;
        int n = s.length();
        vi changed(n, 0);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1] && changed[i - 1] == 0) {
                ans++; changed[i] = 1; continue;
            }
            if (i > 1 && s[i] == s[i - 2] && changed[i - 2] == 0) {
                ans++; changed[i] = 1; continue;
            }
        }
        cout << ans << endl;
    }
}