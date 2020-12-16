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
using cp = complex<double>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    return res;
}

void fft(vector<cp>& a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)
        lg_n++;

    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n))
            swap(a[i], a[reverse(i, lg_n)]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cp wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cp w(1);
            for (int j = 0; j < len / 2; j++) {
                cp u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cp& x : a)
            x /= n;
    }
}

int upper_2(int num) {
    int r = 1;
    while (r < num) {
        r <<= 1;
    }
    return r;
}

int main() {
    int n; cin >> n;
    int m = upper_2(2 * n);
    vector<cp> A(m, 0);
    vector<ll> B(m, 0);
    ll t = 0;
    for (ll i = 1; i < n; i++) {
        t = (t + i * 2 - 1) % n;
        B[t] += 1;
    }
    for (int i = 0; i < n; i++) {
        A[i] = { (double)B[i],0 };
    }
    fft(A, false);
    for (int i = 0; i < m; i++) {
        A[i] = A[i] * A[i];
    }
    fft(A, true);
    //cout << "fft complete" << endl;
    ll ans = 0;
    vector<ll> C(m, 0);
    for (int i = 0; i < m; i++) {
        C[i] = (ll)(A[i].real() + 0.1);
    }
    for (int i = 0; i < 2 * n; i++) {
        if (!B[i % n]) continue;
        ll mul = C[i];
        if (i % 2 == 0) {
            mul += B[i / 2];
        }
        mul >>= 1;
        ans += mul * B[i % n];
    }
    cout << ans << endl;

}

