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
        int n; cin >> n;
        vi A(n), freq(100 + 3 * n, 0), ufreq(100 + 3 * n, 0);
        forn(i, n) {
            cin >> A[i];
            freq[A[i]] ++;
        }
        int cnt = 0;
        for (int i = 1; i <= 2 * n + 1; i ++) {
            if (i > 1 && freq[i - 1] > 0 && (freq[i - 1] + ufreq[i - 1]) > 1) {
                freq[i - 1]--;
                ufreq[i] ++;
            }
            if ((freq[i] + ufreq[i]) > 0) cnt++;
        }
        cout << cnt << endl;
    }
}