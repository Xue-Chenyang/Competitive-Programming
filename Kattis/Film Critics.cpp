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
    fast();
    int n, m, k; cin >> n >> m >> k;
    vector<pair<ll, int>> A(200005);
    for (int i = 0; i < n; i++) {
        cin >> A[i].first;
        A[i].second = i + 1;
    }
    sort(A.begin(), A.begin() + n);
    if (k % m != 0) {
        cout << "impossible" << endl;
        return 0;
    }
    int p = k / m;
    if (p <= 0) {
        cout << "impossible" << endl;
        return 0;
    }
    ll sum = 0;
    vi ans;
    int lp = n - p - 1, rp = n - p;
    sum += m;
    ans.push_back(A[rp].second); rp++;
    for (int i = 1; i < n; i++) {
        if (lp >= 0 && sum > A[lp].first * i) {
            ans.push_back(A[lp].second);
            lp--;
            continue;
        }
        if (rp < n && sum <= A[rp].first * i) {
            sum += m;
            ans.push_back(A[rp].second);
            rp++;
            continue;
        }
        break;
    }
    if (ans.size() != n) {
        cout << "impossible" << endl;
    }
    else {
        for (int i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}