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

const ll MAXLEN = 1e6 + 7;
const ll MOD = 1e9 + 7;
const int MAXN = 1e5 + 7;
int n, q;
string t;
vector<string> songs;
vector<ll> twos(MAXN), sum[26];

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void read(string & p) {
    static char input[MAXLEN];
    scanf("%s", input);
    p = input;
}

int lsone(int l) {
    return l & (-1 * l);
}

void prep_song() {
    while (songs.back().length() < MAXLEN) {
        if (songs.size() >= n + 1) break;
        string nxt = songs.back() + t[songs.size() - 1] + songs.back();
        songs.push_back(nxt);
    }
}

void prep_sum() {
    twos[0] = 1LL;
    for (int i = 1; i < MAXN; i++) {
        twos[i] = (twos[i - 1] * 2) % MOD;
    }
    for (int i = 0; i < 26; i++) {
        sum[i].resize(MAXN, 0);
        char c = 'a' + i;
        for (int j = 1; j <= n; j++) {
            sum[i][j] = (sum[i][j - 1] * 2 + ((t[j - 1] == c) ? 1LL : 0LL)) % MOD;
        }
    }
}

vector<int> kmp(string& d) {
    int back = 0;
    vector<int> dp(d.length(), 0);
    for (int i = 1; i < d.length(); i++) {
        while (back > 0 && d[back] != d[i]) back = dp[back - 1];
        if (d[back] == d[i]) back++;
        dp[i] = back;
    }
    return dp;
}

vector<bool> process(vector<int>& dp, int m) {
    vector<bool> ret(m + 1, false);
    int cur = dp.back();
    while (cur > 0) {
        ret[cur] = true;
        cur = dp[cur - 1];
    }
    ret[0] = true;
    return ret;
}

void solve(int k, string& w) {
    int id = 0;
    while (songs[id].length() < w.length()) id++;
    if (k < id) {
        printf("0\n");
        return;
    }
    string pref = w + "#" + songs[id], suf = songs[id] + "#" + w;
    vector<int> dp_pref = kmp(pref), dp_suf = kmp(suf);
    vector<bool> pref_res = process(dp_pref, w.length()), suf_res = process(dp_suf, w.length());
    ll ans = 0;
    for (int i = 0; i < pref.length(); i++) {
        if (dp_pref[i] == w.length()) ans += 1LL;
    }
    ans = (ans * twos[k - id]) % MOD;

    for (int i = 0; i < w.length(); i++) {
        if (pref_res[i] && suf_res[w.length() - 1 - i]) {
            int c = w[i] - 'a';
            ans = (ans + sum[c][k] - sum[c][id] * twos[k - id]) % MOD;
        }
    }
    ans = (ans + MOD) % MOD;
    printf("%lld\n", ans);
}

int main(){
    scanf("%d%d", &n, &q);
    string s; read(s);
    songs.push_back(s);
    read(t);
    prep_song();
    prep_sum();
    forn(i, q) {
        int k; scanf("%d", &k);
        string w; read(w);
        solve(k, w);
    }
}