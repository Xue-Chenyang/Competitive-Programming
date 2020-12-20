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

typedef long long ll;

int main() {
    int n; cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> B[i];
    }
    string dp[105][30005];
    for (int i = 0; i < 105; i++) {
        for (int j = 0; j < 30005; j++) dp[i][j] = "";
    }

    dp[0][-B[0] + 15000] = "B";
    dp[0][A[0] + 15000] = "A";
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 30000; j++) {
            if (j + B[i] < 30000 && j + B[i] >= 0 && dp[i - 1][j + B[i]] != "") {
                if (dp[i][j] == "") {
                    dp[i][j] = dp[i - 1][j + B[i]] + "B";
                }
                else {
                    dp[i][j] = min(dp[i - 1][j + B[i]] + "B", dp[i][j]);
                }
            }
            if (j-A[i] >= 0&& j-A[i] < 30000 && dp[i - 1][j - A[i]] != "") {
                if (dp[i][j] == "") {
                    dp[i][j] = dp[i - 1][j - A[i]] + "A";
                }
                else {
                    dp[i][j] = min(dp[i - 1][j - A[i]] + "A", dp[i][j]);
                }
            }
        }
    }
    for (int ans = 0; ans <= 10000; ans++) {
        string a = "C", b = "C";
        if (dp[n - 1][ans + 15000] != "") {
            a = dp[n - 1][ans + 15000];
        }
        if (dp[n - 1][15000 - ans] != "") {
             b = dp[n - 1][15000 - ans];
        }
        if (a != "C" || b != "C") {
            cout << min(a, b) << endl;
            break;
        }
    }
}