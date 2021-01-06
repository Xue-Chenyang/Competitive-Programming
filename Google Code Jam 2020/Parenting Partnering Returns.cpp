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
int main() {
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		cin >> n;
		printf("Case #%d: ", _);
		vector<pair<int, pair<int,int>>> A(n);
		forn(i, n) {
			cin >> A[i].first >> A[i].second.first;
			A[i].second.second = i;
		}
		sort(all(A));
		int c = 0, j = 0;
		vector<char> ans(n);
		bool pos = true;
		forn(i, n) {
			if (A[i].first >= c) {
				ans[A[i].second.second] = 'C';
				c = A[i].second.first;
				continue;
			}
			if (A[i].first >= j) {
				ans[A[i].second.second] = 'J';
				j = A[i].second.first;
				continue;
			}
			pos = false;
			printf("IMPOSSIBLE\n");
			break;
		}
		if (pos) {
			for (char ch : ans) {
				printf("%c", ch);
			}
			printf("\n");
		}
	}
}