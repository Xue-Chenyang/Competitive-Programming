#pragma warning( disable : 4996 )
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int lsone(int l) {
    return l & (-1 * l);
}

struct pos {
    int exp;
    int addi;
    int ind;

    bool operator < (const pos& str) const
    {
        if (exp >= 20 || str.exp >= 20) {
            if (exp != str.exp) return exp > str.exp;
            return addi > str.addi;
        }
        else {
            return (1 << exp) + addi > (1 << str.exp) + str.addi;
        }
    }
};

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

class Sell_Compare {
public:
    bool operator() (string id1, string id2) {
        return true;
    }
};

#define forn(i, n) for (int i = 0; i < int(n); i++)

const int AL = 26;
const int MAXN = 400010;

struct trie_node {
    int next[AL];
    trie_node() {
        ms(next, -1);
    }
    int& operator[](int x) {
        return next[x];
    }
};

struct ac_node {
    int next[AL];
    bool leaf;
    int p;
    int pch;
    int link;
    int go[AL];

    ac_node() {
        ms(next, -1);
        ms(go, -1);
        leaf = false;
        link = p = -1;
    }
};

trie_node trie[MAXN];
ac_node ac[MAXN];

int n, m, trie_cnt = 0, ac_cnt = 0, song_ind[MAXN], query_id[MAXN], q_song[MAXN], tin[MAXN], tout[MAXN], f[MAXN], ans[MAXN];
vi suffix_tree[MAXN], song_rev[MAXN], q_song_rev[MAXN];
int T;

int add_letter(int v, int c) {
    if (trie[v][c] == -1) {
        trie[trie_cnt] = trie_node();
        trie[v][c] = trie_cnt;
        trie_cnt++;
    }
    return trie[v][c];
}

int add_string(string s) {
    int v = 0;
    for (auto it : s) {
        int c = it - 'a';
        if (ac[v].next[c] == -1) {
            ac_node nd;
            nd.p = v;
            nd.pch = c;
            ac[ac_cnt] = nd;
            ac[v].next[c] = ac_cnt;
            ac_cnt++;
        }
        v = ac[v].next[c];
    }
    ac[v].leaf = true;
    return v;
}

int go(int v, int ch);

int get_link(int v) {
    //printf("get_link for %d\n", v);
    if (ac[v].link == -1) {
        if (v == 0 || ac[v].p == 0) {
            ac[v].link = 0;
        }
        else {
            ac[v].link = go(get_link(ac[v].p), ac[v].pch);
        }
    }
    return ac[v].link;
}

int go(int v, int ch) {
    if (ac[v].go[ch] == -1) {
        if (ac[v].next[ch] != -1) {
            ac[v].go[ch] = ac[v].next[ch];
        }
        else {
            ac[v].go[ch] = v == 0 ? 0 : go(get_link(v), ch);
        }
    }
    return ac[v].go[ch];
}

void update(int v, int delta) {
    while (v < MAXN) {
        f[v] += delta;
        v += lsone(v);
    }
}

int f_sum(int v) {
    int s = 0;
    while (v > 0) {
        s += f[v];
        v -= lsone(v);
    }
    return s;
}

int f_sum(int left, int right) { //inclusive
    return f_sum(right) - f_sum(left - 1);
}

void dfs_init(int v) {
    tin[v] = T;
    T++;
    for (auto c : suffix_tree[v]) {
        dfs_init(c);
    }
    tout[v] = T;
}

void dfs(int trie_state, int ac_state) {
    update(tin[ac_state], 1);
    for (auto s_id : song_rev[trie_state]) {
        for (auto q_id : q_song_rev[s_id]) {
            ans[q_id] = f_sum(tin[query_id[q_id]], tout[query_id[q_id]] - 1);
        }
    }
    forn(i, AL) {
        if (trie[trie_state][i] != -1) {
            dfs(trie[trie_state][i], go(ac_state, i));
        }
    }
    update(tin[ac_state], -1);
}

char buf[MAXN];

int main() {
    scanf("%d", &n);

    trie[trie_cnt] = trie_node();
    trie_cnt++;

    ac[ac_cnt] = ac_node();
    ac_cnt++;

    forn(i, n) {
        int t; scanf("%d", &t);
        if (t == 1) {
            scanf("%s", buf);
            song_ind[i] = add_letter(0, buf[0] - 'a');
        }
        else {
            int u; scanf("%d", &u);
            scanf("%s", buf);
            song_ind[i] = add_letter(song_ind[u - 1], buf[0] - 'a');
        }
        song_rev[song_ind[i]].push_back(i);
    }

    scanf("%d", &m);
    forn(i, m) {
        int j; scanf("%d", &j); j--;
        q_song[i] = j;
        q_song_rev[j].push_back(i);
        scanf("%s", buf);
        query_id[i] = add_string(buf);
    }

    for (int i = 1; i < ac_cnt; i++) {
        suffix_tree[get_link(i)].push_back(i);
    }

    T = 1;
    dfs_init(0);
    dfs(0, 0);

    forn(i, m) {
        printf("%d\n", ans[i]);
    }

    return 0;
}