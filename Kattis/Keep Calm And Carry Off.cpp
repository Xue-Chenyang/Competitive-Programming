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

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define se second
#define fi first
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)
#include <bits/stdc++.h>

typedef long long ll;

bool les(vi& A, vi& B) {
    int al = A.size()-1;
    while (al >= 0 && A[al] == 0) {
        al--;
    }
    int bl = B.size() - 1;
    while (bl >= 0 && B[bl] == 0) {
        bl--;
    }
    if (al < bl) return true;
    if (al > bl) return false;
    for (int i = al; i >= 0; i--) {
        if (A[i] < B[i]) {
            return true;
        }
        if (A[i] > B[i]) {
            return false;
        }
    }
    return true;
}

void pr(vi& A) {
    int al = A.size() - 1;
    while (A[al] == 0) {
        al--;
    }
    if (al < 0) {
        cout << 0 << endl;
        return;
    }
    for (int i = al; i >= 0; i--) {
        cout << A[i];
    }
    cout << endl;

}
int main() {
    fast();
    string A, B;
    cin >> A >> B;
    int l = -1, al = A.length(), bl = B.length();
    for (int i = 0; i < min(al,bl); i++) {
        if (A[al - 1 - i] - '0' + B[bl - 1 - i] - '0' > 9) {
            l = i;
        }
    }
    if (l < 0) {
        cout << 0 << endl;
        return 0;
    }
    while (true) {
        if (l + 1 < min(al, bl) && A[al - 1 - (l + 1)] - '0' + B[bl - 1 - (l + 1)] - '0' == 9) {
            l++;
        }
        else {
            break;
        }
    }
    vector<int> ca, cb;
    bool ba = true, bb = true;
    for (int i = al - 1; i >= al - 1 - l; i--) {
        if (ba) {
            if (A[i] == '0') {
                ca.push_back(0);
            }
            else {
                ca.push_back(10 - (A[i] - '0'));
                ba = false;
            }
        }
        else {
            ca.push_back(9 - (A[i] - '0'));
        }
    }
    for (int i = bl - 1; i >= bl - 1 - l; i--) {
        if (bb) {
            if (B[i] == '0') {
                cb.push_back(0);
            }
            else {
                cb.push_back(10 - (B[i] - '0'));
                bb = false;
            }
        }
        else {
            cb.push_back(9 - (B[i] - '0'));
        }
    }
    if (les(ca, cb)) {
        pr(ca);
    }
    else {
        pr(cb);
    }
    return 0;
}