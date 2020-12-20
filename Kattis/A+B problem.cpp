#pragma warning( disable : 4996 )
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <numeric>
#include <random>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
#include <set>
#include <complex>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
    int n;                                         // n = (int)A.size()
    vi A, st, lazy;                                // the arrays

    int l(int p) { return  p << 1; }                 // go to left child
    int r(int p) { return (p << 1) + 1; }              // go to right child

    int conquer(int a, int b) {
        if (a == -1) return b;                       // corner case
        if (b == -1) return a;
        return max(a, b);                            // RMQ
    }

    void build(int p, int L, int R) {              // O(n)
        if (L == R)
            st[p] = A[L];                              // base case
        else {
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m + 1, R);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

    void propagate(int p, int L, int R) {
        if (lazy[p] != 0) {                         // has a lazy flag
            st[p] = st[p] + lazy[p];                           // [L..R] has same value
            if (L != R) {                          // not a leaf
                lazy[l(p)] = lazy[l(p)] == 0 ? lazy[p] : lazy[l(p)] + lazy[p];
                lazy[r(p)] = lazy[r(p)] == 0 ? lazy[p] : lazy[r(p)] + lazy[p];
            }// propagate downwards
            else {            // L == R, a single index
                A[L] = A[L] + lazy[p];
            }// time to update this
            lazy[p] = 0;                              // erase lazy flag
        }
    }

    int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
        propagate(p, L, R);                          // lazy propagation
        if (i > j) return -1;                        // infeasible
        if ((L >= i) && (R <= j)) return st[p];      // found the segment
        int m = (L + R) / 2;
        return conquer(RMQ(l(p), L, m, i, min(m, j)),
            RMQ(r(p), m + 1, R, max(i, m + 1), j));
    }

    void update(int p, int L, int R, int i, int j, int val) { // O(log n)
        propagate(p, L, R);                          // lazy propagation
        if (i > j) return;
        if ((L >= i) && (R <= j)) {                  // found the segment
            lazy[p] = val;                             // update this
            propagate(p, L, R);                        // lazy propagation
        }
        else {
            int m = (L + R) / 2;
            update(l(p), L, m, i, min(m, j), val);
            update(r(p), m + 1, R, max(i, m + 1), j, val);
            int lsubtree = (lazy[l(p)] != 0) ? lazy[l(p)] + st[l(p)] : st[l(p)];
            int rsubtree = (lazy[r(p)] != 0) ? lazy[r(p)] + st[r(p)] : st[r(p)];
            st[p] = (lsubtree >= rsubtree) ? st[l(p)] : st[r(p)];
        }
    }

    void forcePropagate(int p, int L, int R) {
        st[p] = st[p] + lazy[p];                           // [L..R] has same value
        if (L != R) {                          // not a leaf
            lazy[l(p)] = lazy[l(p)] == 0 ? lazy[p] : lazy[l(p)] + lazy[p];
            lazy[r(p)] = lazy[r(p)] == 0 ? lazy[p] : lazy[r(p)] + lazy[p];
            int m = (L + R) / 2;
            forcePropagate(l(p), L, m);
            forcePropagate(r(p), m + 1, R);
        }// propagate downwards
        else {            // L == R, a single index
            A[L] = A[L] + lazy[p];
        }// time to update this
        lazy[p] = 0;
    }

public:
    SegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n, 0) {}

    SegmentTree(const vi _A) : SegmentTree((int)_A.size()) {
        A = _A;
        build(1, 0, n - 1);
    }

    void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

    int RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }

    void forcePrint() {
        forcePropagate(1, 0, n - 1);
        for (int c : A) {
            cout << c << " ";
        }
        cout << endl;
    }
};

int lsone(int l) {
    return l & (-1 * l);
}

struct pos {
    int key;
    int value;

    bool operator < (const pos& str) const
    {
        if (value != str.value) {
            return value < str.value;
        }
        else {
            return key > str.key;
        }
    }
};

typedef pair<int, int> ii;

// Lowest Common Ancestor
/**

const int L = 20;

int n, m, T = 0;

vi ori, cur, parent, tin, tout, psum;
vector<ii> adj;
vector<vi> ancestors;

void dfs(int u, int p) {
    tin[u] = T;
    T++;
    parent[u] = p;
    ancestors[u][0] = p;
    for (int i = 1; i < L; i++) {
        ancestors[u][i] = ancestors[ancestors[u][i - 1]][i - 1];
    }
    if (u >= m) {
        int left = adj[u - m].first, right = adj[u - m].second;
        dfs(left, u);
        dfs(right, u);
    }
    tout[u] = T;
}

bool is_ancestor(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = L - 1; i >= 0; i--) {
        if (!is_ancestor(ancestors[u][i], v)) {
            u = ancestors[u][i];
        }
    }
    return parent[u];
}
**/



ll n, cnt0, len;

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

const ll M = 50000;

vector<ll> freq(100005);

int main() {
    scanf("%lld", &n);
    ll c = 0;
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &c);
        if (!c) {
            cnt0++;
        }
        c += M;
        freq[c] ++;
        len = max(len, c + 1);
    }
    ll l = 1;
    while (l < 2 * len) {
        l <<= 1;
    }
    vector<cp> a(l, cp{ 0,0 });
    for (ll i = 0; i < len; i++) {
        a[i] = cp( freq[i], 0 );
    }
    fft(a, false);
    for (ll i = 0; i < l; i++) {
        a[i] *= a[i];
    }
    fft(a, true);
    vector<ll> ans(l, 0);
    for (ll i = 0; i < l; i++) {
        ans[i] = (ll)(a[i].real() + 0.5);
    }
    ll res = 0;
    for (ll i = 0; i < len; i++) {
        if (freq[i]) {
            if ((i*2-M >= 0) && (i*2-M < len) && freq[i * 2 - M]) {
                res -= freq[i] * freq[i * 2 - M];
            }
            res += freq[i] * ans[i + M];
        }
    }
    res -= cnt0 * (n - 1) * 2;
    printf("%lld\n", res);
}