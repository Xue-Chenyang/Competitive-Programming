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

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<ii> ans;
        int cur = n;
        for (int i = n - 1; i > 2; i--) {
            if (cd(cur, i) >= i) {
                ans.push_back({ n, i });
                cur = cd(cur, i);
            }
            ans.push_back({ i,n });
        }
        while (cur != 1) {
            ans.push_back({ n,2 });
            cur = cd(cur, 2);
        }
        cout << ans.size() << endl;
        for (ii p : ans) {
            cout << p.first << " " << p.second << endl;
        }
    }
}