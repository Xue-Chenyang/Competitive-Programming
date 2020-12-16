
#include <bits/stdc++.h>
using namespace std;

int main() {
	int k, w, l; cin >> k>>w>>l;
	int mul = 1;
	int t = 2;
	for (int i = 2; i <= k; i ++) {
		t <<=1;
		mul += t;
	}
	mul += t;
	double ta = 2 * (double) l /((double) mul * (double) w);
	double PI = M_PI;
	double a = atan(ta) * 180 / PI;
	cout << fixed << setprecision(7);
	cout << a << endl;
}
