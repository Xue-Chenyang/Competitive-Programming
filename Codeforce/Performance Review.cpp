#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // The length of original array

const int INF = 1e9;

int A[MAXN], st[MAXN * 4], lazy[MAXN * 4], n; // A is the oriiginal data, n is the actual size of data

int m, q, R, N;
vector<vector<int>> C;

void build(int p, int l, int r) {
    if (l == r) {
        st[p] = A[l];
        return;
    }
    build(p << 1, l, (l + r) / 2);
    build((p << 1) + 1, (l + r) / 2 + 1, r);
    st[p] = min(st[p << 1], st[(p << 1) + 1]);
}

void build() {
    build(1, 0, n - 1);
}

void push_down(int p, int l, int r) { // implementation depends on what update and query means, here is the version for range increment/decrement update and range minimum query
    if (lazy[p] == 0) return;
    st[p] += lazy[p];
    if (l != r) {
        lazy[p << 1] += lazy[p];
        lazy[(p << 1) + 1] += lazy[p];
    }
    lazy[p] = 0;
}

void update(int delta, int p, int l, int r, int ql, int qr) {
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
        st[p] = min(st[p << 1], st[(p << 1) + 1]); // This depends on what update means
    }
}

void update(int delta, int l, int r) { // range update of delta from left to right inclusive
    if (l > r) return;
    update(delta, 1, 0, n - 1, l, r);
}

int query(int p, int l, int r, int ql, int qr) {
    push_down(p, l, r);
    if (l >= ql && r <= qr) {
        return st[p];
    }
    int mid = (l + r) / 2;
    int ans = INF;
    if (ql <= mid) {
        ans = min(ans, query(p << 1, l, mid, ql, qr));
    }
    if (qr > mid) {
        ans = min(ans, query((p << 1) + 1, mid + 1, r, ql, qr));
    }
    return ans;
}

int query(int l, int r) {
    return query(1, 0, n - 1, l, r);
}

int main() {
    scanf("%d%d%d", &N, &m, &q);
    C.assign(m, vector<int>());
    scanf("%d", &R);
    int rank = 1;
    for (int i = 1; i < N; i ++) {
        int l; scanf("%d", &l);
        if (l < R) {
            rank ++;
        }
    }
    for (int i = 0; i < m; i ++) {
        int v; scanf("%d", &v);
        A[i] = rank - v;
        C[i].resize(v);
        for (int j = 0; j < v; j ++) {
            scanf("%d", &C[i][j]);
            if (C[i][j] > R) {
                rank --;
            }
        }
    }
    n = m;

    // for (int i = 0; i < m; i ++) {
    //     printf("%d ", A[i]);
    // }
    // printf("\n");

    build();

    for (int i = 0; i < q; i ++) {
        int y, j, d;
        scanf("%d%d%d", &y, &j, &d); j --;
        //printf("C[%d][%d] is %d\n", y-1, j, C[y-1][j]);
        if (C[y-1][j] < R && d > R) {
            //printf("sub from %d to %d\n", y, n-1);
            update(-1, y, n-1);
        } else if (C[y-1][j] > R && d < R) {
            //printf("increase from %d to %d\n", y, n-1);
            update(1, y, n-1);
        }
        if (query(0, n-1) <= 0) {
            printf("0\n");
        } else {
            printf("1\n");
        }
        C[y-1][j] = d;
    }
}