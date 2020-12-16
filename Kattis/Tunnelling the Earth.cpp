#include <bits/stdc++.h>
using namespace std;

double R = 6371009;

struct P { double x,y,z;};
P operator+(const P &a, const P &b) {
	return {a.x  +b.x, a.y+b.y, a.z + b.z};
}
P operator*(double scale, const P &a) {
	return {scale * a.x, scale * a.y, scale * a.z};
}
double dist( P a ,P b) {
	return sqrt(pow(fabs(a.x - b.x),2) + pow(fabs(a.y - b.y),2) + pow(fabs(a.z - b.z),2));
}

double PI = M_PI;

P toPoint(double lat, double lng) {
	lat *= PI / 180.0;
	lng *= PI / 180.0; 
	double x = R * cos(lng);
	double y = R * sin(lng);
	P v1 = {x , y , 0};
	P v2 = {0 , 0 , R};
	P ans = cos(lat) * v1 + sin(lat) * v2;
	return ans;
}

int main() {
	int t; cin>>t;
	while (t--) {
		double lat1, long1, lat2, long2;
		cin>>lat1>>long1>>lat2>>long2;
		P p1 = toPoint(lat1 , long1);
		P p2 = toPoint(lat2 , long2);
		double sd = dist(p1, p2);
		double angle = acos(1 - sd * sd / (2 * R * R));
		double cd = R * angle;
		
		printf("%.7f\n", cd - sd);
	
	}
}
