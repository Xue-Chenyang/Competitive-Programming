#include <bits/stdc++.h>

using namespace std;

vector<int> classa, classb;
typedef long long ll;
bool compare (vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

ll MOD = 1000003;
int classno = 1;
ll fact(ll n) {
    ll ans = 1;
    for (int i = 1; i <= n; i++) ans = (ans * i) % MOD;
    return ans;
}

int main() {

    int n; cin>>n;
    int m; cin>>m;
    classa.assign(n,0);
    classb = classa;

    while (m--) {
        vector<int> inputa(n), inputb(n);
        
        for (int i = 0; i < n; i++) {
            char c; cin>>c;
            inputa[i] = c - '0';
        }
         for (int i = 0; i < n; i++) {
            char c; cin>>c;
            inputb[i] = c - '0';
        }

        vector<int> aon, aoff, bon, boff;
        
        for (int i = 0; i < n; i++) {
            if (inputa[i] == 1) {
                aon.push_back(classa[i]);
            } else {
                aoff.push_back(classa[i]);
            }
        }

        for (int i = 0; i < n; i++) {
            if (inputb[i] == 1) {
                bon.push_back(classb[i]);
            } else {
                boff.push_back(classb[i]);
            }
        }

        if (!compare(aon, bon) || !compare(aoff, boff)) {
            cout<<0; return 0;
        }

        unordered_map<int,int> mapon, mapoff;
        for (int i = 0; i < n; i++) {
            if (inputa[i] == 1) {
                if (!mapon.count(classa[i])) mapon[classa[i]] = classno++;
            } else {
                if (!mapoff.count(classa[i])) mapoff[classa[i]] = classno++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (inputa[i] == 1) classa[i] = mapon[classa[i]];
            else classa[i] = mapoff[classa[i]];
        }


        for (int i = 0; i < n; i++) {
            if (inputb[i] == 1) classb[i] = mapon[classb[i]];
            else classb[i] = mapoff[classb[i]];
        }
    }

    // for (auto it: classa) cout<<it<<' '; cout<<endl;

    // for (auto it: classb) cout<<it<<' '; cout<<endl;
    map<int, int> occur;
    for (int i = 0; i < n; i++) {
        occur[classa[i]]++;
    } 

    ll ans = 1;

    for (auto it: occur) {
        ans = (ans * fact(it.second)) % MOD;
    }
    cout<<ans;
}