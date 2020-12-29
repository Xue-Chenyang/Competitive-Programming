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


int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> present(n);
        for (int i = 0; i < n; i++) {
            cin >> present[i];
        }
        vector<int> absent; int ptr = 0;
        for (int i = 1; i <= 2 * n; i++) {
            if (ptr < n && present[ptr] == i) {
                ptr++;
            }
            else {
                absent.push_back(i);
            }
        }
        reverse(absent.begin(), absent.end());
        vector<int> pos(n);
        ptr = n;
        for (int i = 0; i < n; i++) {
            while (ptr > 0 && present[i] > absent[ptr - 1]) ptr--;
            pos[i] = ptr;
        }
        int ma = 0, mi = 0, m = n + 1;
        for (int i = 0; i <= n; i++) {
            if (i <n) m = min(m, pos[i] + i);
            if (m < i + 1) {
                ma = i; break;
            }
        }
        for (int i = 0; i < n; i++) {
            pos[i] = n - pos[i];
        }
        reverse(pos.begin(), pos.end());
        m = n + 1;
        for (int i = 0; i <= n; i++) {
            if (i <n) m = min(m, pos[i] + i);
            if (m < i + 1) {
                mi = i; break;
            }
        }
        mi = n - mi;
        cout << ma - mi + 1 << endl;
    }
}