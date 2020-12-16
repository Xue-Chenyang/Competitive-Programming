
#include <bits/stdc++.h>
using namespace std;

int main() {
	int tc;
	cin >> tc;
	while (tc --) {
		int mask = 0;
		int p,w,d,l,pt;
		string s; cin >> s;
		if (s[0] != '?') {
			p = stoi(s);
			mask += 1;
		}
		mask <<= 1;
		cin >> s;
		if (s[0] != '?') {
			w = stoi(s);
			mask += 1;
		}
		mask <<= 1;
		cin >> s;
		if (s[0] != '?') {
			d = stoi(s);
			mask += 1;
		}
		mask <<= 1;
		cin >> s;
		if (s[0] != '?') {
			l = stoi(s);
			mask += 1;
		}
		mask <<= 1;
		cin >> s;
		if (s[0] != '?') {
			pt = stoi(s);
			mask += 1;
		}
		int mi;
		switch (mask) {
			case 1:
				mi = pt / 3 + pt % 3;
				if (mi == 100) {
					w = pt / 3; d = pt % 3; l = 0; p = 100;
				}
				break;
				
			case 2:
				if (l == 100) {
					p = 100; w = 0; d = 0; pt = 0;
				}
				break;
				
			case 3:
				if (pt < 3) {
					d = pt; w = 0; p = w+d+l;
				}
				mi = pt / 3 + pt % 3;
				if (mi + 2 + l > 100) {
					w = pt / 3; d = pt % 3;
					p = d+w+l;
				}
				break;
				
			case 4:
				if (d == 100) {
					p = 100; pt = 100; w = 0; l = 0;
				}
				break;
				
			case 5:
				mi = (pt - d) / 3;
				if (mi + d == 100) {
					p = 100; w = mi; l = 0;
				}
				break;
				
			case 6:
				if (d + l == 100) {
					p = 100; w= 0; pt = d;
				}
				break;
				
			case 8:
				if (w == 100) {
					p = 100; d = 0; l = 0; pt = 300;
				}
				break;
				
			case 9:
				if ((pt - 3*w) + w == 100) {
					d = pt - 3*w;
					l = 0;
					p = w+d+l;
				}
				break;
				
			case 10:
				if (w + l == 100) {
					d = 0;
					p = 100;
					pt = 3*w +d;
				}
				break;
				
			case 12:
				if (w+d==100) {
					l = 0; p =100;
					pt = 3*w+d;
				}
				break;
				
			case 13:
				if (w+d==100) {
					l = 0; p =100;
				}
				break;
				
			case 7:
				w = (pt - d) / 3; p = w+d+l;
				break;
				
			case 11:
				d = pt - w*3;
				p = w+d+l;
				break;
				
			case 14:
				pt = w*3+d; p = w+d+l;
				break;
				
			case 15:
				p = w+d+l;
				break;
				
			case 16:
				if (p == 0) {
					d = 0; w = 0; l = 0; pt = 0;
				}
				break;
				
			case 17:
				if (pt < 3) {
					w = 0; d = pt; l = p-d;
				} else {
					mi = pt / 3 + pt % 3;
					if (p <= mi + 1) {
						w = pt / 3; d = pt % 3; l = p-mi;
					}
				}
				break;
				
			case 18:
				if (p == l) {
					w = 0; d = 0; pt = 0;
				}
				break;
				
			case 19:
				w = (pt + l - p) / 2;
				d = p-w-l;
				break;
				
			case 20:
				if (p == d) {
					w = 0; l = 0; pt = d;
				}
				break;
				
			case 21:
				w = (pt - d) / 3;
				l = p-w-d;
				break;
				
			case 22:
				w = p-d-l; pt = 3*w+d;
				break;
			
			case 23:
				w = p-l-d; break;
				
			case 24:
				if (p == w) {
					d = 0; l = 0; pt = 3*w;
				}
				break;
				
			case 25:
				d = pt - 3*w;
				l = p-w-d;
				break;
				
			case 26:
				d = p-w-l;
				pt = 3*w+d;
				break;
				
			case 27:
				d= p-w-l;
				break;
				
			case 28:
				l = p-w-d;
				pt = 3*w+d;
				break;
				
			case 29:
				l = p-w-d;
				break;
				
			case 30:
				pt = 3*w+d;
				break;
		}
		cout << p << " " << w << " " << d << " " << l << " " << pt << endl;
	}
}
