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
    priority_queue<pair<int, int>> pq;
    forn(i, n) {
        int l; cin >> l; 
	if (l > 0) pq.push({ l,i + 1 });
    }
    vector<pair<int, int>> ans;
    while (true) {
        if (pq.size() <= 1) break;
        auto [a, ia] = pq.top(); pq.pop();
        auto [b, ib] = pq.top(); pq.pop();
        a--; b--;
        ans.push_back({ ia,ib });
        if (a > 0) {
            pq.push({ a,ia });
        }
        if (b > 0) {
            pq.push({ b,ib });
        }
    }
    if (pq.size() == 1) {
        cout << "no\n";
    }
    else {
        cout << "yes\n";
        for (auto [a, b] : ans) {
            cout << a << " " << b << endl;
        }
    }
    return 0;
}