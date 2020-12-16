#include <bits/stdc++.h>
using namespace std;

int main() {
	
	double n,c;
	cin>>n>>c;
	
	
	
	vector<int> cards(n);
	for (int i = 0; i < n; i++) {
		cin>>cards[i];
	}
	
	
	if (c == 0) {
		double tot = 0;
		for (auto it: cards) tot += it;
		tot /= n;
		printf("%.5f", tot);
		return 0;
	
		
	}
	sort(cards.begin(), cards.end(), greater<double>());
	vector<double> avg(n+2, 0);
	double total = 0;
	for (int i = 0; i < n; i++) {
		total += cards[i];
		avg[i + 1] = total / ((double) (i + 1)); 
	}
	
	double ttn = 0;
	for (int i = 1; i < n; i++) {
		ttn += cards[i];
	}
	ttn /= ((double) (n-1));
	
	vector<double> plc(n+2 , 0);
	plc[1] = c/n;
	double sum =  plc[1];
	for (int i = 2; i <= n - c + 1; i++) {
		plc[i] = (1.0 - sum) * (c / (n - i + 1));
		sum += plc[i];
	} 
	//for (int i = 1; i <= n - c + 1; i++) printf("PLC = %d = %.2f\n" , i, plc[i]);
	//
	double ans = 0;
	for (int i = 2; i <= n - c + 1; i++) {
		ans += plc[i] * avg[i-1];
	}
	ans += plc[1] * ttn;
	printf("%.5f", ans);
	
	
	
	
	
	
	
	
	
}
