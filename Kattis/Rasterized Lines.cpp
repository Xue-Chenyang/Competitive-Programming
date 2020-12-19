#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000005
typedef long long ll;

vector<ll> primes;
bool isp[MAXN];

ll ans = 0;
vector<pair<ll, int>> pfactors;

void seive() {
    for (ll i = 2; i < MAXN; i ++) {
        if (!isp[i]) {
            primes.push_back(i);
                //cout << i << " ";
            for (ll j = i * i; j < MAXN; j += i) {
                isp[j] = true;
            }
        }
    }
}

void factorise(ll n) {
    pfactors.clear();
    int ptr = 0;
    while (primes[ptr] * primes[ptr] <= n) {
        int freq = 0;
        while (n % primes[ptr] == 0) {
            n /= primes[ptr];
            freq ++;
        }
        if (freq>0) {
            pfactors.push_back({primes[ptr], freq});
        }
        ptr++;
        if (ptr >= primes.size()) break;
    }
    if (n > 1) {
        pfactors.push_back({n, 1});
    }
}

ll mpr(ll m, ll p) {
    if (p == 0) return 1;
    ll ans = mpr(m, p /2);
    ans = ans * ans;
    if (p&1) ans *= m;
    return ans;

}

ll tot(ll n) {
    int ptr = 0;
    ll ans = 1;
    //cout << "tot for " << n;
    while (primes[ptr] * primes[ptr] <= n) {
        ll temp = 1;
        ll freq = 0;
        while (n % primes[ptr] == 0) {
            freq ++;
            n /= primes[ptr];
        }
        if (freq > 0) {
            temp = mpr(primes[ptr], freq - 1) * (primes[ptr] - 1);
            ans = ans * temp;
        }
        ptr ++;
        if (ptr >= primes.size()) break;
    }
    if (n > 1) {
        ans = ans * (n-1);
    }
    //cout << " is " << ans << endl;
    return ans;
}

void solve(int idx, ll t) {
    if (idx >= pfactors.size()) {
        ans += tot(t + 1);
        return;
    }
    ll m = 1;
    for (int i = 0; i <= pfactors[idx].second; i ++) {
        solve(idx + 1, t * m);
        m *= pfactors[idx].first;
    }
}

int main() {
    seive();
    int t; cin>>t; while(t--) {
        ans = 0;
        ll n; cin>>n;
        factorise(n);

        solve(0, 1);
        cout << ans << endl;
    }
}