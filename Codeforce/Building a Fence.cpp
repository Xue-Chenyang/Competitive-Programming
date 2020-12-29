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
    int tc; cin >> tc;
    while (tc--) {
        int n;
        cin >> n; int k; cin >> k;
        vi low(n), high(n);
        for (int i = 0; i < n; i++) {
            cin >> low[i];
            high[i] = (i == 0 || i == n - 1) ? low[i] : low[i] + k - 1;
        }
        int l = -5e8, h = 5e8;
        bool flag = true;
        for (int i = 0; i < n; i++) {
            l -= k - 1; h += k - 1;
            l = max(l, low[i]); h = min(h, high[i]);
            if (l > h) {
                flag = false;
                break;
            }
        }
        if (flag){
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}