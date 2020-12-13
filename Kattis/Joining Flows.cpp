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

struct tap {
    ll temp, l, u;
};

class comparator {
public:

    bool operator()(tap t1, tap t2) {
        return t1.temp < t2.temp;
    }
};

int main() {
    int n; 
    fast(); cin >> n;
    vector<tap> vt;
    ll flow_l = 0, flow_u = 0;
    forn(i, n) {
        ll t, l, u; cin >> t >> l >> u;
        flow_u += u; flow_l += l;
        vt.push_back(tap{ t,l,u });
    }
    sort(vt.begin(), vt.end(), comparator());
    ll tl = 0;
    for (tap t : vt) {
        tl += t.temp * t.l;
    }
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        ll flow, temp; cin >> temp >> flow;
        if (flow < flow_l || flow > flow_u) {
            cout << "no" << endl;
            continue;
        }
        ll tot = flow * temp;
        ll lower_b = tl, upper_b = tl;
        ll excess = flow - flow_l;
        int p = 0;
        while (excess > 0) {
            lower_b += min(excess, vt[p].u - vt[p].l) * vt[p].temp;
            excess -= min(excess, vt[p].u - vt[p].l);
            p++;
        }
        p = n - 1; excess = flow - flow_l;
        while (excess > 0) {
            upper_b += min(excess, vt[p].u - vt[p].l) * vt[p].temp;
            excess -= min(excess, vt[p].u - vt[p].l);
            p--;
        }
        if (tot <= upper_b && tot >= lower_b) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
}
