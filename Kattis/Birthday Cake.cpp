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

const double EPS = 1e-9;
typedef long long ll;
struct P { double x, y; }; P dummy; // point
struct L { double a, b, c; }; // line
struct LS { P a, b; }; // line segment
P operator+(const P& a, const P& b) { return { a.x + b.x, a.y + b.y }; }
P operator-(const P& a, const P& b) { return { a.x - b.x, a.y - b.y }; }
P operator-(const P& a) { return { -a.x,-a.y }; }
P operator*(double s, const P& a) { return { s * a.x, s * a.y }; }
bool operator<(const P& a, const P& b) { return a.x < b.x || a.x == b.x && a.y < b.y; }
bool operator==(const P& a, const P& b) { return fabs(a.x - b.x) + fabs(a.y - b.y) < EPS; }
double dist(const P& a, const P& b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }
double dot(const P& a, const P& b) { return a.x * b.x + a.y * b.y; }
double cross(const P& a, const P& b) { return a.x * b.y - a.y * b.x; }
P rotate(P& a, double rad) { return { a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad) }; }
L pointsToLine(P& a, P& b) {
    if (fabs(a.x - b.x) < EPS) return { 1,0,-a.x };
    L l = { -(a.y - b.y) / (a.x - b.x),1,0 };
    return l.c = -(l.a * a.x) - a.y, l;
}
bool operator||(const L& a, const L& b) { return fabs(a.a - b.a) + fabs(a.b - b.b) < EPS; } // parallel
bool operator==(const L& a, const L& b) { return (a || b) && fabs(a.c - b.c) < EPS; }
bool intersect(L& a, L& b, P& p) {
    if (a || b) return false;
    p.x = (b.b * a.c - a.b * b.c) / (b.a * a.b - a.a * b.b);
    p.y = (fabs(a.b) > EPS) ? -(a.a * p.x + a.c) : -(b.a * p.x + b.c);
    return true;
}
void toLS(L& l, LS& ls) {
    double a = l.a, b = l.b, c = l.c;
    ls.a = { 0,-c };
    ls.b = { -c / a,0 };
}
double proj(LS& ls, P& p, P& proj = dummy, bool clamp = true) {
    double l2 = pow(dist(ls.a, ls.b), 2);
    if (fabs(l2) < EPS) { proj = p; return dist(p, ls.a); }
    double t = dot(p - ls.a, ls.b - ls.a) / l2;
    if (clamp) t = max(0.0, min(1.0, t));
    proj = ls.a + t * (ls.b - ls.a);
    return dist(p, proj);
}

int ccw(P& p, P& q, P& r) { // -1/0/1 for right/coll/left
    double c = cross(q - p, r - p);
    if (fabs(c) < EPS) return 0;
    if (c > 0) return 1;
    return -1;
}
bool LSintersect(LS& a, LS& b, P& p = dummy) { // check if Line Segment a & b intersect, store in p
    L al = pointsToLine(a.a, a.b);
    L bl = pointsToLine(b.a, b.b);
    bool res = intersect(al, bl, p);
    if (res && abs(proj(a, p) < EPS) && abs(proj(b, p) < EPS)) return true;
    return false;
}
vector<P> convexHull(vector<P>& pts) {
    int n = pts.size(), k = 0;
    vector<P> H(2 * n);
    if (n <= 3) return H = pts;
    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; i++) {
        while (k >= 2 && ccw(H[k - 2], H[k - 1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {             // build upper hull
        while (k >= t && ccw(H[k - 2], H[k - 1], pts[i - 1]) <= 0) k--;
        H[k++] = pts[i - 1];
    }
    H.resize(k - 1); return H;
}
double perimeter(vector<P>& pts) {
    if (!(pts.back() == pts.front()) || pts.size() == 1) pts.push_back(pts.front());
    double total = 0;
    for (int i = 0; i < pts.size() - 1; i++) total += dist(pts[i], pts[i + 1]);
    return total;
}
ll area2(vector<P>& pts) {
    ll total = 0;
    for (int i = 0; i < (int)pts.size() - 1; i++) {
        total += (pts[i].x * pts[i + 1].y - pts[i + 1].x * pts[i].y);
    }
    return abs(total);
}

int n, m; double r;
int main() {
    cin >> n >> m >> r;
    vector<P> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<L> lines(m);
    int regions = 1;
    for (int i = 0; i < m; i++) {
        double a, b, c;
        cin >> a >> b >> c;
        if (fabs(b) < EPS) {
            lines[i] = { 1,0,c / a };
        }
        else {
            lines[i] = { a / b, 1, c / b };
        }
        int cnt = 1;
        for (int j = 0; j < i; j++) {
            P inter;
            if (intersect(lines[i], lines[j], inter)) {
                if (dist({ 0,0 }, inter) < r) {
                    cnt++;
                }
            }
        }
        regions += cnt;
    }
    if (regions != n) {
        cout << "no\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            L l1 = pointsToLine(pts[i], pts[j]);
            bool cross = false;
            for (L l2 : lines) {
                P inter;
                if (intersect(l1, l2, inter)) {
                    if (fabs(dist(inter, pts[i]) + dist(inter, pts[j]) - dist(pts[i], pts[j])) < EPS) {
                        cross = true;
                        break;
                    }
                }
            }
            if (!cross) {
                cout << "no\n";
                return 0;
            }
        }
    }
    cout << "yes\n";
}