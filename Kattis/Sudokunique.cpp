#pragma warning( disable : 4996 )
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18; // INF = 1e18, not 2^63-1 to avoid overflow
const int FULL = (1 << 9) - 1;
int n, bo[81], op[81], solution, freeN, ans[81];
unordered_set<int> options[10];

int getIdx(int row, int col) {
    return row * 9 + col;
}

int lsOne(int l) {
    return l & (-1 * l);
}

bool removeCandidate(int idx, int can, vi &changed) {
    if (op[idx] & (1 << can)) {
        changed.push_back(idx);
        op[idx] -= 1 << can;
        int current = __builtin_popcount(op[idx]);
        options[current + 1].erase(idx);
        options[current].emplace(idx);
        return true;
    }
    else {
        return false;
    }
}

void addCandidate(int idx, int can) {
    op[idx] += 1 << can;
    int current = __builtin_popcount(op[idx]);
    options[current - 1].erase(idx);
    options[current].emplace(idx);
}

void search() {
    /*
    cout << "current board with " << freeN << " node left" << endl;
    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 9; k++) {
            if (op[getIdx(j, k)] == 0) {
                cout << bo[getIdx(j, k)] + 1;
            }
            else {
                cout << 0;
            }
            if (k < 8) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
    */
    if (freeN == 0) {
        if (solution == 0) {
            for (int j = 0; j < 81; j++) {
                ans[j] = bo[j];
            }
            solution = 1;
        }
        else {
            solution = 2;
        }
        return;
    }
    int idx;
    for (int o = 1; o <= 9; o++) {
        if (options[o].empty()) {
            continue;
        }
        idx = *options[o].begin();
        options[o].erase(idx);
        break;
    }
    int x = idx / 9;
    int y = idx % 9;
    int temp = op[idx];
    int record = temp;
    op[idx] = 0;
    freeN--;
    while (temp > 0) {
        vi changed;
        int choice = lsOne(temp);
        temp -= choice;
        choice = log2(choice) + 0.1;
        for (int j = 0; j < 9; j++) {
            if (j != x) {
                int neigh = getIdx(j, y);
                if (removeCandidate(neigh, choice, changed)) {
                    if (op[neigh] == 0) {
                        for (int rem : changed) {
                            addCandidate(rem, choice);
                        }
                        goto BACK;
                    }
                }
            }
            if (j != y) {
                int neigh = getIdx(x, j);
                if (removeCandidate(neigh, choice, changed)) {
                    if (op[neigh] == 0) {
                        for (int rem : changed) {
                            addCandidate(rem, choice);
                        }
                        goto BACK;
                    }
                }
            }
        }
        int rg = x / 3;
        int cg = y / 3;
        for (int j = rg * 3; j < rg * 3 + 3; j++) {
            for (int k = cg * 3; k < cg * 3 + 3; k++) {
                if (j == x && k == y) {
                    continue;
                }
                int neigh = getIdx(j, k);
                if (removeCandidate(neigh, choice, changed)) {
                    if (op[neigh] == 0) {
                        for (int rem : changed) {
                            addCandidate(rem, choice);
                        }
                        goto BACK;
                    }
                }
            }
        }
        bo[idx] = choice;
        //cout << "updated (" << x << ", " << y << ") to " << choice + 1 << endl;
        search();
        if (solution == 2) {
            return;
        }
        for (int c : changed) {
            addCandidate(c, choice);
        }
    }
    BACK: op[idx] = record;
    int num = __builtin_popcount(record);
    options[num].emplace(idx);
    freeN++;
}

int main() {
    //freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (true) {
        bool consistent = true;
        solution = 0;
        freeN = 81;
        for (int j = 0; j < 81; j++) {
            op[j] = FULL;
        }
        for (int j = 0; j <= 9; j++) {
            options[j].clear();
        }
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                int idx = getIdx(j, k);
                int l;
                if (!(cin >> l)) {
                    return 0;
                }
                bo[idx] = l;
                if (consistent && bo[idx] != 0) {
                    freeN--;
                    bo[idx] --;
                    if (!(op[idx] & (1 << bo[idx]))) {
                        consistent = false;
                    }
                    op[idx] = 0;
                    int mask = (FULL - (1 << bo[idx]));
                    for (int x = 0; x < 9; x++) {
                        if (x == j) {
                            continue;
                        }
                        op[getIdx(x, k)] = op[getIdx(x, k)] & mask;
                    }
                    for (int y = 0; y < 9; y++) {
                        if (y == k) {
                            continue;
                        }
                        op[getIdx(j, y)] = op[getIdx(j, y)] & mask;
                    }
                    int rg = j / 3;
                    int cg = k / 3;
                    for (int x = rg * 3; x < (rg + 1) * 3; x++) {
                        for (int y = cg * 3; y < (cg + 1) * 3; y++) {
                            if (x == j && y == k) {
                                continue;
                            }
                            op[getIdx(x, y)] = op[getIdx(x, y)] & mask;
                        }
                    }
                }
            }
        }
        if (!consistent) {
            goto FAIL;
        }
        for (int j = 0; j < 81; j++) {
            n = __builtin_popcount(op[j]);
            options[n].emplace(j);
        }
        search();
        if (solution == 0) {
            FAIL: cout << "Find another job" << endl;
        }
        else if (solution == 1) {
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    cout << ans[getIdx(j, k)] + 1;
                    if (k < 8) {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
        else {
            cout << "Non-unique" << endl;
        }
        if (cin.eof()) {
            goto END;
        }
        cout << endl;
    }
    END: return 0;
}
