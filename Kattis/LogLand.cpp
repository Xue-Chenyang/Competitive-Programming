#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
typedef long long ll;

ll MOD = 1e9 + 7;
ll mod2[1000001];

int main() {
	
	mod2[0] = 1;
	for (int i = 1; i <= 1e6; i++) {
		ll temp = mod2[i-1];
		temp = (temp * 2) % MOD;
		mod2[i] = temp;
	}
	
	int k; cin>>k;
	vector<ll> arr(k);
	for (auto &i: arr) cin>>i;
	
	ll acc = 0;
	ll ans = 0;
	for (int i = 0; i < k; i++) {
		if (arr[i] % 2 == 0) {
			acc += arr[i];
			acc /= 2;
		} else {
			if (acc == 0) {
				ans += mod2[i];
				ans %= MOD;
			} 
			acc += arr[i];
			acc /= 2;	
		}
	}
	cout<< ans;
}
