#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
typedef long long ll;
struct P {double x,y;}; P dummy;
struct L {double a,b,c;};
struct LS {P a,b;};
P operator+(const P &a, const P &b) {return {a.x + b.x, a.y + b.y};}
P operator-(const P &a, const P &b) {return {a.x - b.x, a.y - b.y};}
P operator-(const P &a) {return {-a.x, -a.y};}
P operator*(double s, const P &a) { return {s * a.x, s * a.y};}
bool operator< (const P &a,const P &b) {return a.x < b.x || a.x == b.x && a.y < b.y;}
bool operator==(const P &a, const P &b) {return fabs(a.x - b.x) + fabs(a.y - b.y) < EPS;}
double dot(const P &a, const P &b) {return a.x*b.x + a.y*b.y;}
double dist(const P &a, const P &b) {return sqrt(pow(a.x - b.x , 2) + pow(a.y - b.y , 2));}
double cross(const P &a, const P &b) {return a.x * b.y - a.y * b.x;}
P rotate(P &a, double rad) {return {a.x*cos(rad) - a.y*sin(rad) , a.x*sin(rad) + a.y*cos(rad)};}
L pointsToLine(P &a, P &b) {
	if (fabs(a.x - b.x) < EPS) return {1 , 0, -a.x};
	L l = {-(a.y-b.y)/(a.x-b.x),1,0};
	return l.c = -(l.a*a.x) - a.y, l;}
bool operator||(const L &a, const L &b) {return fabs(a.a - b.a) + fabs(a.b - b.b) < EPS;}
bool operator==(const L &a, const L &b) {return (a || b) && fabs(a.c - b.c) < EPS;}
bool intersect(L &a, L &b, P &p) {
	if (a || b) return false;
	p.x = (b.b*a.c-a.b*b.c)/(b.a*a.b - a.a*b.b);
	p.y = (fabs(a.b) > EPS)? -(a.a*p.x + a.c) : - (b.a*p.x + b.c);
	return true;
}

double PI = 3.14159265358979323;

int main() {
	
	int n;
	while(cin>>n , n) {
		P a,b,c;
		cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
		L ab = pointsToLine(a,b);
		L bc = pointsToLine(b,c);
		P abmid = 0.5 * (a + b);
		P bcmid =  0.5 * (b + c);
		P abvec = b - abmid;
		abvec = rotate(abvec, PI / 2.0);
		 P temp = abmid + abvec;
		 P t2 = abmid - abvec;
		 //printf("AB perp %.2f %.2f %.2f %.2f\n", temp.x, temp.y, t2.x, t2.y);
		L abp = pointsToLine(temp , t2); 
		
		P bcvec = c - bcmid;
		bcvec = rotate(bcvec, PI / 2.0);
		temp = bcmid + bcvec;
		t2 = bcmid - bcvec;
		//printf("BC perp %.2f %.2f %.2f %.2f\n", temp.x, temp.y, t2.x, t2.y);
		L bcp = pointsToLine(temp , t2);
		//printf(" abmid = %.2f %.2f, bcmid = %.2f, %.2f\n", abmid.x, abmid.y, bcmid.x, bcmid.y);
		P center;
		//printf("%.2fx + %.2fy + %.2f = 0\n" , bcp.a, bcp.b, bcp.c);		
		intersect(bcp,abp,center);
		
		//printf("Center of circle = %.2f , %.2f\n", center.x, center.y);
		P cv = a - center;
		
		double minx, miny, maxx, maxy;
		minx = miny = 1e9;
		maxx = maxy = -1e9;
		
		for (int i = 0; i < n; i++) {
			P polypoint = center + cv;
			
			minx = min(minx , polypoint.x);
			miny = min(miny , polypoint.y);
			maxx = max(maxx , polypoint.x);
			maxy = max(maxy , polypoint.y);

			
			cv = rotate(cv , 2 * PI / ((double)(n)));

		}
		printf("%.9f\n", (maxx - minx) * (maxy - miny));
	}
}

