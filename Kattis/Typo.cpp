#include <bits/stdc++.h>
using namespace std;

struct vertex {
    bool leaf;
    vector<int> next;
    int p; int pch;
    public: vertex() {
        leaf = false;
        next.assign(26, -1);
    }
};

vector<vertex> trie(1);
int addString(string &s) {
    int v = 0;
    for (char &c : s) {
        int ch = c - 'a';
        if (trie[v].next[ch] == -1) {
            trie[v].next[ch] = (int)(trie.size());
            trie.emplace_back();
            trie.back().p = v;
            trie.back().pch = c-'a';
        }
        v = trie[v].next[ch];
    }
    trie[v].leaf = true;
    return v;
}

bool dfs(string &s, int rm, int id, int curr) {
    if (id == (int)(s.size())) {
        if (!rm || !trie[curr].leaf) return false;
        return true;
    }
    for (int i = 0; i < 26; i++) {
        if (trie[curr].next[i] == -1) continue;
        if (i == s[id] - 'a') {
            if (dfs(s, rm, id + 1, trie[curr].next[i])) return true;
        }
        if (rm < 1) {
            if (dfs(s, rm + 1, id + 2, trie[curr].next[i])) return true;
        }
    }
    return false;
}

bool go(int p, vector<int>& suf, int ind) {
    if (ind < 0) {
        return trie[p].leaf;
    }
    if (trie[p].next[suf[ind]] < 0) {
        return false;
    }
    return go(trie[p].next[suf[ind]], suf, ind - 1);
}

bool typo(int p, int ind, vector<int>& suf) {

    if (!suf.empty()) {
        if (go(p, suf, suf.size() - 2)) {
            return true;
        }
    }
    if (ind < 0) return false;
    suf.push_back(trie[p].pch);
    return typo(trie[p].p, ind -1, suf);
}

int main() {
    int n; cin >> n;
    vector<string> v(n);
    vector<int> labels(n);
    for (int i = 0; i < n; i ++) {
        
        cin >> v[i];
        labels[i] = addString(v[i]);
    }
    bool ac = false;
    for (int i = 0; i < n; i++) {
        vector<int> l;
        bool a = typo(labels[i], v[i].size()-1, l);
        if (a) {
            cout << v[i] << endl;
            ac = true;
        }
    }
    if (!ac) cout << "NO TYPOS";
}