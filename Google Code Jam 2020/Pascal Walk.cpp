#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
using namespace std;

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<int> vi;

int n, tc;

void sweep(int& r, int& k) {
	if (k == 1) {
		for (int i = 1; i <= r; i++) {
			cout << r << " " << i << endl;
		}
		r++; k = r;
	}
	else {
		for (int i = k; i >= 1; i--) {
			cout << r << " " << i << endl;
		}
		r++; k = 1;
	}
}

void adv(int& r, int& k) {
	if (k == 1) {
		cout << r << " " << k << endl;
		r++;
	}
	else {
		cout << r << " " << k << endl;
		r++; k++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		cin >> n;
		cout << "Case #" << _ << ": \n";
		if (n < 500) {
			for (int i = 0; i < n; i++) {
				cout << i + 1 << " 1\n";
			}
			continue;
		}
		int m = n - 30;
		int l = 0;
		while ((1 << l) <= n) l++;
		int r = 1, k = 1, s = 0;
		for (int i = 1; i <= l; i++) {
			if (m & (1 << (i - 1))) {
				sweep(r, k);
				s += (1 << (i - 1));
			}
			else {
				adv(r, k);
				s += 1;
			}
		}
		for (int i = s; i < n; i++) {
			adv(r, k);
		}
	}
}