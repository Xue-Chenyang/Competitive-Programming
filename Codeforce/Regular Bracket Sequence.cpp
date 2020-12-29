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
 
int main() {
    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;
        if (s.length() & 1) {
            cout << "NO" << endl;
            continue;
        }
        unordered_set<int> se[2];
        se[1].insert(0);
        for (int i = 0; i < s.length(); i++) {
            for (int c : se[(i & 1) ^ 1]) {
                if (s[i] == '(') {
                    se[i & 1].insert(c + 1);
                }
                else if (s[i] == ')') {
                    if (c > 0) se[i & 1].insert(c - 1);
                }
                else {
                    se[i & 1].insert(c + 1);
                    if (c > 0) {
                        se[i & 1].insert(c - 1);
                    }
                }
            }
            se[(i & 1) ^ 1].clear();
        }
        if (se[((s.length() - 1) & 1)].count(0)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}