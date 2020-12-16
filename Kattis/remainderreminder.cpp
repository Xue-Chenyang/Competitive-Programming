#pragma warning( disable : 4996 )
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

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

ll a, b, c, d, e, f, g;

bool p[100000];
vi primes, highest_power, rem;

ll mpr(ll m, ll p) {
    if (p == 0) return 1;
    ll ans = mpr(m, p / 2);
    ans = ans * ans;
    if (p & 1) ans = ans * m;
    return ans;
}

void seive() {
    for (int i = 2; i < 100000; i++) {
        if (p[i]) {
            primes.push_back((ll)i);
            for (ll j = (ll)i * i; j < 100000; j += i) {
                p[j] = false;
            }
        }
    }
}

void process(ll base, ll r) {
    int ptr = 0;
    while (base >= primes[ptr] * primes[ptr]) {
        int l = 0;
        while (base % primes[ptr] == 0) {
            base /= primes[ptr];
            l++;
        }
        if (l > highest_power[primes[ptr]]) {
            highest_power[primes[ptr]] = l;
            rem[primes[ptr]] = r % mpr(primes[ptr], l);
        }
        ptr++;
    }
    if (base > 1) {
        if (1 > highest_power[base]) {
            highest_power[base] = 1;
            rem[base] = r % base;
        }
    }
}

ll extendedEuclid(ll a, ll b, ll& x, ll& y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a / b;
        ll t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    return a;
}


int main() {
    cin >> a >> b;
    vector<ll> s;
    for (int i = 1; i <= min(a, b) / 2; i++) {
        s.push_back(i * (a - 2 * i) * (b - 2 * i));
    }
    ms(p, true);
    sort(all(s), greater<ll>());
    cin >> c >> d >> e;
    seive();
    highest_power.assign(100000, 0);

    rem.assign(100000, 0);

    process(s[0], c); process(s[1], d); process(s[2], e);
    ll base = -1, r = -1;

    for (int i = 0; i < primes.size(); i++) {
        if (highest_power[primes[i]] == 0) continue;
        if (base < 0) {
            base = mpr(primes[i], highest_power[primes[i]]);
            r = rem[primes[i]];
            continue;
        }
        ll alpha, beta, nb = mpr(primes[i], highest_power[primes[i]]);
        extendedEuclid(base, nb, alpha, beta);
        //cout << alpha * base + beta * nb << endl;
        r = (r * (beta * nb) + rem[primes[i]] * (alpha * base));
        base = base * nb;
        r = r % base;
        if (r < 0) r += base;
    }
    cin >> f >> g;
    if (f > r) {
        r += ((f - r) / base) * base;
        if (r < f) r += base;
    }
    else if (r > g) {
        r -= ((r - g) / base) * base;
        if (r > g) r -= base;
    }
    cout << r << endl;
}

