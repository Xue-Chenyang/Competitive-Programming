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
#include <bits/stdc++.h>

typedef long long ll;

int main() {
    int n; cin >> n;
    string s[1000];
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    bool pos = false;
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            if (s[i].length() == s[i + 1].length()) {
                char t = s[i][0];
                s[i][0] = '9';
                if (stoll(s[i]) > stoll(s[i + 1])) {
                    pos = true;
                    break;
                }
                else {
                    s[i][0] = t;
                }
            }
        }
        if (i > 0) {
            if (s[i].length() == s[i - 1].length()) {
                char st = s[i].length() == 1 ? '0' : '1';
                if (stoll(st + s[i].substr(1, s[i].length())) < stoll(s[i - 1])) {
                    pos = true;
                    s[i][0] = st;
                    break;
                }
            }
        }
    }
    if (pos) {
        for (string str : s) {
            cout << str << " ";
        }
    }
    else {
        cout << "impossible\n";
    }
    return 0;
}