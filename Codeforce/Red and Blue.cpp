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
        int n;
        cin >> n;
        vector<int> A(n);
        int M1 = 0;
        for (int i = 0; i < n; i++) {
            cin >> A[i];
            if (i>0) A[i] += A[i - 1];
            M1 = max(M1, A[i]);
        }
        
        int m; cin >> m; int M2 = 0;
        vector<int> B(m);
        for (int i = 0; i < m; i++) {
            cin >> B[i];
            if (i > 0) B[i] += B[i - 1];
            M2 = max(M2, B[i]);
        }
        cout << M1 + M2 << endl;
    }
}