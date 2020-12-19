#include <bits/stdc++.h>
using namespace std;

double amt;
double eval(double x) {
    double y = amt - x;
    return x * y;
}

int main() {
    double amt; cin >> amt;
    if (amt > 1.0) {
        cout << 0.25;
        return 0;

    }
    double ans = amt / 2.0;
    cout << fixed << setprecision(6) << ans * ans;
    /*
    double lo = 0.0, hi = 0.0;
    while (hi - lo > 1e-9) {
        double m1 = hi - (hi - lo) / 3.0;
        double m2 = lo + (hi - lo) / 3.0;
        double f1 = eval(m1), f2 = eval(m2);
        if (f1 < f2) {
            lo = m1;
        } else hi = m2;
    }
    cout << fixed << setprecision(6) << eval(lo);
    */
}