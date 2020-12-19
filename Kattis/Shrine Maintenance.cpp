#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
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
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)
int n, d, D[6], w;
vector<int> shs;
vector<double> pres;

double const EPS = 1e-6;


double dist(int a, int b) {
    if (a < b) a += n;
    double theta = M_PI * (a - b) / n * 2;
    return sqrt(2.0 * 1000 * 1000 * (1 - cos(theta)));
}

int main() {
    while (true) {
        cin >> w;
        if (w == 0) break;
        cin >> n;
        cin >> d;
        for (int i = 0; i < d; i++) {
            cin >> D[i];
        }
        shs.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < d; j++) {
                if (i % D[j] == 0) {
                    shs.push_back(i);
                    break;
                }
            }
        }
        pres.assign(shs.size() + 1, 0);
        for (int i = 1; i < shs.size(); i++) {
            pres[i] = pres[i - 1] + dist(shs[i], shs[i - 1]);
        }
        pres[shs.size()] = pres[shs.size() - 1] + dist(0, shs.back());
        double left = 0, right = pres.back();
        while (right - left > EPS) {
            double mid = (right + left) / 2;
            vector<int> ep(n);
            for (int i = 0; i < shs.size(); i++) {
                double b = pres[i] + mid;
                if (b > pres.back()) b -= pres.back();
                int pos = distance(pres.begin(), lower_bound(pres.begin(), pres.end(), b));
                if (pres[pos] > b) {
                    pos = (pos + n - 1) % n;
                }
                ep[i] = pos;
            }
            //cout << "For " << mid << ":\n";
            //for (int i = 0; i < shs.size(); i++) {
            //    cout << shs[i] << " ends at " << ep[i] << endl;
            //}
            bool ok = false;
            for (int st = 0; st < shs.size(); st++) {
                int cur = st, cnt = 0, covered = 0; 
                while (cnt < w) {
                    cnt++;
                    if (ep[cur] < cur) {
                        covered += ep[cur] + shs.size() - cur + 1;
                    }
                    else {
                        covered += ep[cur] - cur + 1;
                    }
                    cur = (ep[cur] + 1) % shs.size();
                }
                if (covered >= shs.size()) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                right = mid;
            }
            else {
                left = mid;
            }
        }
        printf("%.1f\n", left + 2000);
    }
}