#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cout << fixed << setprecision(1);
    int n; scanf("%d", &n);
    ll ans1 = 0;
    vector<pair<ll,ll>> p;
    for (int i = 0 ; i < n; i ++) {
        ll a,b; scanf("%lld%lld",&a,&b);
        ans1 = max(ans1, a*b);
        if (a > b) {
            p.push_back({a,b});
        } else {
            p.push_back({b,a});
        }
    }
    sort(p.begin(), p.end());
    //cout << p.size() << endl;
    ll ans2 = 0, m1 = 0, m2 = 0;
    for (int i = n - 1; i >= 0; i --) {
        //cout << p[i].first << " " << p[i].second << endl;
        if (p[i].second > m1) {
            m2 = m1;
            m1 = p[i].second;
        } else if (p[i].second > m2) {
            m2 = p[i].second;
        }
        ans2 = max(ans2, p[i].first * m2);
    }
    if (ans1 > 2 * ans2) {
        if (ans1 % 2 == 0) {
            printf("%lld.0", ans1/2);
        } else {
            printf("%lld.5", ans1/2);
        }
    } else {
        printf("%lld.0", ans2);
    }
}