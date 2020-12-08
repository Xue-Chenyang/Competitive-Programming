#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll MOD = 1e9+7;
 
struct mat{
    ll a11,a12,a21,a22;
    mat() {
        a11 = a12 = a21 = a22 = 0;
    }
    mat(int a, int b, int c, int d) {
        a11 = a; a12 = b; a21 = c; a22 = d;
    }
    // mat operator* (mat & other) {
    //     ll A = ((a11 * other.a11) % MOD + (a12 * other.a21) % MOD) % MOD;
        
    //     ll B = ((a11 * other.a12) % MOD + (a12 * other.a22) % MOD) % MOD;
        
    //     ll C = ((a21 * other.a11) % MOD + (a22 * other.a21) % MOD) % MOD;
 
    //     ll D = ((a21 * other.a12) % MOD + (a22 * other.a22) % MOD) % MOD;
    //     return mat(A,B,C,D);
    // } 
};
 
mat operator* (mat a , mat other) {
    ll A = ((a.a11 * other.a11) % MOD + (a.a12 * other.a21) % MOD) % MOD;
    ll B = ((a.a11 * other.a12) % MOD + (a.a12 * other.a22) % MOD) % MOD;
    ll C = ((a.a21 * other.a11) % MOD + (a.a22 * other.a21) % MOD) % MOD;
    ll D = ((a.a21 * other.a12) % MOD + (a.a22 * other.a22) % MOD) % MOD;
    return mat(A,B,C,D);
} 
 
mat inv(mat m) {
    return mat(m.a22, m.a21, m.a12, m.a11);
}
 
pair<ll,ll> mul(ll a, ll b, mat m) {
    ll A = ((a * m.a11) % MOD + (b * m.a21) % MOD) % MOD;
    ll B = ((a * m.a12) % MOD + (b * m.a22) % MOD) % MOD;
    return {A,B};
}
 
void print_mat(mat m) {
    printf("%lld  %lld\n%lld  %lld\n", m.a11, m.a12, m.a21, m.a22);
}
int n,m;
char buf[100005];
mat st[500005];
bool lazy[500005];
 
void build(int p, int l, int r) {
    lazy[p] = false;
    if (l == r) {
        if (buf[l] == 'A') {
            st[p] = mat(1,0,1,1);
        } else {
            st[p] = mat(1,1,0,1);
        }
        // printf("mat for [%d, %d] is :\n", l, r);
        // print_mat(st[p]);
        return;
    }
    
    build(p << 1, l, (l + r) / 2);
    build((p << 1) + 1, (l + r) / 2 + 1, r);
 
    st[p] = st[p << 1] * st[(p << 1) + 1];
    // printf("mat for [%d, %d] is :\n", l, r);
    // print_mat(st[p]);
}
 
void push_down(int p, int l, int r) {
    if (!lazy[p]) return;
    st[p] = inv(st[p]);
    if (l != r) {
        lazy[p << 1] = !lazy[p << 1];
        lazy[(p << 1) + 1] = !lazy[(p << 1) + 1];
    }
    lazy[p] = false;
}
 
void update(int p, int l, int r, int ql, int qr) {
    push_down(p,l,r);
    if (ql > r || qr < l) return;
    if (l >= ql && r <= qr) {
        lazy[p] = ! lazy[p];
        push_down(p, l, r);
    } else {
        int mid = (l + r) / 2;
        update(p << 1, l, mid, ql, qr);
        update((p << 1) + 1, mid + 1, r, ql, qr);
        st[p] = st[p << 1] * st[(p << 1) + 1];
    }
}
 
mat query(int p,  int l, int r, int ql, int qr) {
    push_down(p,l,r);
    if (l >= ql && r <= qr) {
        return st[p];
    }
    int mid = (l+r)/2;
    if (ql <= mid && qr > mid) {
        return query(p << 1, l, mid, ql, qr) * query((p << 1) + 1, mid + 1, r, ql, qr);
    }
    if (ql <= mid) {
        return query(p << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        return query((p << 1) + 1, mid + 1, r, ql, qr);
    }
}
 
void update(int l, int r) {
    update(1, 0, n-1, l, r);
}
 
mat query(int l, int r) {
    return query(1, 0, n-1, l, r);
}
 
int main() {
    // while (true) {
    //     ll a,b,c,d; cin >> a>>b>>c>>d;
    //     mat m1(a,b,c,d);
    //     cin >> a>>b>>c>>d;
    //     mat m2(a,b,c,d);
    //     print_mat(m1*m2);
    // }
    scanf("%d%d", &n, &m);
    scanf("%s", buf);
    build(1, 0, n-1);
    for (int i = 0; i < m; i ++) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int l, r; scanf("%d%d", &l, &r); l--; r--;
            update(l, r);
        } else {
            int l, r; scanf("%d%d", &l, &r); l--; r--;
            ll a, b; scanf("%lld%lld", &a, &b);
            mat re = query(l, r);
            //print_mat(re);
            pair<ll,ll> ans = mul(a,b,re);
            printf("%lld %lld\n", ans.first, ans.second);
        }
    }
}