#include <bits/stdc++.h>
using namespace std;

string process(string& s, int l, int r, vector<int>& pre) {
    if (l > r) {
        return "";
    }
    int last = l;
    vector<string> subs;
    for (int i = l; i <= r; i ++) {
        if (pre[i+1] == pre[l]) {
            subs.push_back("0" + process(s, last+1, i-1, pre) + "1");
            last = i + 1;
        }
    }
    sort(subs.begin(), subs.end());
    string m = "";
    for (int i = 0; i < subs.size(); i ++) {
        m += subs[i];
    }
    return m;
}

int main() {
    int tc; cin >> tc;
    while (tc --) {
        string s1, s2;
        cin >> s1 >> s2;
        if(s1.size() != s2.size()) {
            cout << "different\n";
            continue;
        }
        int n = s1.size();
        vector<int> pre1(n+1), pre2(n+1);
        for (int i = 0; i <= n; i ++) {
            if (i == 0) {
                pre1[i] = 0;
                pre2[i] = 0;
            } else {
                int d =s1[i-1] == '0' ? -1 : 1;
                pre1[i] = pre1[i-1] + d;
                d = s2[i-1] == '0' ? -1:1;
                pre2[i] = pre2[i-1] +d;
            }
        }
        s1 = process(s1, 0, n-1, pre1);
        s2 = process(s2, 0, n-1, pre2);
        if (s1 == s2) {
            cout << "same\n";
        } else {
            cout << "different\n";
        }
    }
}