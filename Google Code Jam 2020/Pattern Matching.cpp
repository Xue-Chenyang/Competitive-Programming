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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		cout << "Case #" << _ << ": ";
		cin >> n;
		vector<pair<int, string>> prefix, suffix;
		string ans;
		forn(i, n) {
			string s; cin >> s;
			int p = 0;
			for (int j = 0; j < s.length(); j++) {
				if (s[j] == '*') {
					if (p == 0) {
						if (j == 0) {
							p++;
						}
						else {
							string pre = s.substr(0, j);
							prefix.push_back({ j, pre });
							p = j + 1;
						}
					}
					else {
						ans += s.substr(p, j - p);
						p = j + 1;
					}
				}
			}
			if (p != s.length()) {
				suffix.push_back({ s.length() - p, s.substr(p, s.length() - p) });
			}
		}
		sort(prefix.begin(), prefix.end(), greater<pair<int, string>>());
		sort(suffix.begin(), suffix.end(), greater<pair<int, string>>());

		bool ok = true;
		if (prefix.size() > 1) {
			string comp = prefix[0].second;
			for (int i = 1; i < prefix.size(); i++) {
				string tarr = prefix[i].second;
				bool flag = true;
				for (int j = 0; j < tarr.length(); j++) {
					if (tarr[j] != comp[j]) {
						flag = false; break;
					}
				}
				if (!flag) {
					ok = false; break;
				}
			}
			if (!ok) {
				cout << "*\n";
				continue;
			}
		}
		if (suffix.size() > 1) {
			string comp = suffix[0].second;
			for (int i = 1; i < suffix.size(); i++) {
				bool flag = true;
				string tarr = suffix[i].second;
				for (int j = 0; j < tarr.length(); j++) {
					if (tarr[tarr.length() - 1 - j] != comp[comp.length() - 1 - j]) {
						flag = false; break;
					}
				}
				if (!flag) {
					ok = false; break;
				}
			}
			if (!ok) {
				cout << "*\n";
				continue;
			}
		}
		if (!prefix.empty()) {
			ans = prefix[0].second + ans;
		}
		if (!suffix.empty()) {
			ans = ans + suffix[0].second;
		}
		cout << ans << endl;
	}
}