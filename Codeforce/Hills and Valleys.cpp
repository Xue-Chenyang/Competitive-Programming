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

int tc,n;

int tr(vi & A, int i, int v) {
	int s = 0;
	if (i - 2 >= 0 && A[i - 1] > A[i - 2] && A[i - 1] > v) s++;
	if (i - 2 >= 0 && A[i - 1] < A[i - 2] && A[i - 1] < v) s++;
	if (i + 2 < n && A[i + 1] > A[i + 2] && A[i + 1] > v) s++;
	if (i + 2 < n && A[i + 1] < A[i + 2] && A[i + 1] < v) s++;
	return s;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	cin >> tc;
	while (tc--) {
		//int n;
		cin >> n;
		vi A(n), v(n,0);
		forn(i, n) cin >> A[i];
		int s = 0;
		for (int i = 1; i < n - 1; i++) {
			if (A[i] > A[i - 1] && A[i] > A[i + 1]) {
				v[i] = 1; s++;
			}
			if (A[i] < A[i - 1] && A[i] < A[i + 1]) {
				v[i] = 1; s++;
			}
		}
		int m = 0;
		for (int i = 1; i < n-1; i++) {
			m = max(m, v[i - 1] + v[i] + v[i + 1] - tr(A, i, A[i - 1]));
			m = max(m, v[i - 1] + v[i] + v[i + 1] - tr(A, i, A[i + 1]));
		}
		cout << s - m << endl;
	}
}
