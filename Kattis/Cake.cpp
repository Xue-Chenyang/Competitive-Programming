
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int main() {
	int r,c,n;
	cin >> r >> c >> n;
	vector<ii> A;
	for (int i= 0; i < n; i ++) {
		int a,b; cin >>a>>b;
		A.push_back({a,b});
	}
	//cout << "!" << endl;
	sort(A.begin(), A.end());
	int lastR = 1;
	int i = 0;
	while (i < n) {
		//cout << i << endl;
		int j = i;
		while (j+1 < n && A[j+1].first == A[j].first) {
			j ++;
		}
		int lastC = 1;
		
		int er = j == n - 1? r : A[i].first;
		for (int k = i; k < j; k ++) {
			cout << lastR << " " << lastC << " " << er << " " << A[k].second << endl;
			lastC = A[k].second+1;
		}
		cout << lastR << " " << lastC << " " << er << " " << c << endl;
		lastR = A[i].first+1;
		i = j + 1;
	}
	cout << 0 << endl;
}
