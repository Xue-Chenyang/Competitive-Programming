#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> iii;

iii parse(string s) {
	return {stoi(s.substr(0,4)), stoi(s.substr(4,2)), stoi(s.substr(6,2))};
}

int merit, demerit;

void pr(int y, int m, int d, int mp, int dm) {
	cout << y << "-";
	if (m < 10) {
		cout << 0 << m << "-";
	} else {
		cout << m << "-";
	}
	if (d < 10) {
		cout << 0 << d;
	} else {
		cout << d;
	}
	if (mp == 0 && dm == 0) {
		cout << " No merit or demerit points." << endl;
		return;
	}
	if (mp > 0) {
		cout << " " << mp << " merit point(s)." << endl;
		return;
	}
	
	cout << " " << dm << " demerit point(s)." << endl;
}

bool earlier(int y1, int m1, int d1, int y2, int m2, int d2) {
	if (y1 != y2) return y1<y2;
	if (m1!=m2) return m1<m2;
	if (d1!=d2) return d1<d2;
	return true;
}

int main() {
	string s; cin >> s;
	iii dd = parse(s);
	int y,m,d; tie(y,m,d) = dd;
	int ny = y + 1, yeven = y;
	merit = 0; demerit = 0;
	pr(y,m,d,merit,demerit);
	while (cin >> s, !cin.eof()) {
		int Y,M,D; tie(Y,M,D) = parse(s);
		int v; cin >> v;
		while (earlier(ny, m, d, Y, M ,D)) {
			if (demerit > 0) {
				demerit = max(0, min(demerit - 2, demerit / 2));
				if (demerit == 0) {
					yeven = ny;
				}
				pr(ny,m,d,merit, demerit);
			} else {
				if (ny - yeven > 0 && (ny-yeven) % 2 == 0 && merit<5) {
					merit ++;
					pr(ny,m,d,merit, demerit);
				}
			}
			ny ++;
		}
		if (merit > 0) {
			if (v > merit * 2) {
				demerit = v-merit*2;
				merit = 0;
				pr(Y, M, D, merit, demerit);
			} else {
				int deduct = v/2;
				if (v%2 != 0) deduct ++;
				merit -= deduct;
				yeven = Y;
				pr(Y, M, D, merit, demerit);
			}
		} else {
			demerit += v;
			pr(Y, M, D, merit, demerit);
		}
		ny = Y+1; m=M; d=D;
	}
	while (true) {
		if (demerit > 0) {
			demerit = max(0, min(demerit - 2, demerit / 2));
			if (demerit == 0) {
				yeven = ny;
			}
			pr(ny,m,d,merit, demerit);
		} else {
			if (ny - yeven > 0 && (ny-yeven) % 2 == 0) {
				merit ++;
				pr(ny,m,d,merit, demerit);
				if (merit >= 5) break;
			}
		}
		ny ++;
	}
}
