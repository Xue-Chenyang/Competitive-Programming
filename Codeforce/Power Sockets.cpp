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
typedef vector<int> vi;

const int MAXN = 200000; // The length of original array

const int INF = 1e9;

ll A[MAXN], st[MAXN * 4], lazy[MAXN * 4], n; // A is the oriiginal data, n is the actual size of data

void build(int p, int l, int r) {
    if (l == r) {
        st[p] = A[l];
        return;
    }
    build(p << 1, l, (l + r) / 2);
    build((p << 1) + 1, (l + r) / 2 + 1, r);
    st[p] = (st[p << 1] + st[(p << 1) + 1]);
}

void build() {
    build(1, 0, n - 1);
}

void push_down(int p, int l, int r) { // implementation depends on what update and query means, here is the version for range increment/decrement update and range minimum query
    if (lazy[p] == 0) return;
    st[p] += lazy[p] * (r - l + 1);
    if (l != r) {
        lazy[p << 1] += lazy[p];
        lazy[(p << 1) + 1] += lazy[p];
    }
    lazy[p] = 0;
}

void update(ll delta, int p, int l, int r, int ql, int qr) {
    push_down(p, l, r);
    if (ql > r || qr < l) return;
    if (l >= ql && r <= qr) {
        lazy[p] += delta;
        push_down(p, l, r);
    }
    else {
        int mid = (l + r) / 2;
        update(delta, p << 1, l, mid, ql, qr);
        update(delta, (p << 1) + 1, mid + 1, r, ql, qr);
        st[p] = (st[p << 1] + st[(p << 1) + 1]); // This depends on what update means
    }
}

void update(int delta, int l, int r) { // range update of delta from left to right inclusive
    update(delta, 1, 0, n - 1, l, r);
}

ll query(int p, int l, int r, int ql, int qr) {
    push_down(p, l, r);
    if (l >= ql && r <= qr) {
        return st[p];
    }
    int mid = (l + r) / 2;
    ll ans = 0;
    if (ql <= mid) {
        ans += query(p << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        ans += query((p << 1) + 1, mid + 1, r, ql, qr);
    }
    return ans;
}

int query(int l, int r) {
    return query(1, 0, n - 1, l, r);
}

int trav(int p, int l, int r, int cnt) {
    push_down(p, l, r);
    if (l == r)
        return l;
    int mid = (l + r) / 2;
    push_down(p * 2, l, mid);
    push_down((p * 2) + 1, mid, r);
    int res = INF;
    if (st[p * 2] >= cnt)
        res = trav(p * 2, l, mid, cnt);
    else if (st[(p * 2) + 1] >= cnt - st[p * 2])
        res = trav((p * 2) + 1, mid + 1, r, cnt - st[p * 2]);
    st[p] = st[p * 2] + st[p * 2 + 1];
    return res;
}


int main() {
    int N, target; cin >> N >> target;
    vi leng(N); ll tot = 1;
    for (int i = 0; i < N; i++) {
        cin >> leng[i];
        tot += leng[i] - 2;
    }
    if (tot < target) {
        cout << -1 << endl;
        return 0;
    }
    sort(leng.begin(), leng.end(), greater<int>());
    memset(A, 0, sizeof A);
    A[0] = 1;
    n = MAXN;
    build();
    int ans = INF, stat = 0;
    for (int i : leng) {
        while (query(0, stat) == 0) {
            stat++;
        }
        update(-1, stat, stat);
        update(1, stat + 2, stat + 1 + (i - 1) / 2);
        update(1, stat + 2, stat + 1 + i / 2);
        ans = min(ans, trav(1, 0, n - 1, target));
        //cout << stat << " " << ans << endl;
    }
    cout << ans << endl;
    return 0;
}