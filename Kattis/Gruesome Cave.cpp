#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int movs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

int main() {

    int r, c;
    cin >> r >> c;
    getchar();
    vector<vector<char>> M(r, vector<char>(c));

    vector<vector<int>> cnt(r, vector<int>(c, 0));
    int s, e;
    for (int i = 0; i < r; i ++) {
        string str;
        getline(cin, str);
        for (int j = 0; j < c; j ++) {
            M[i][j] = str[j];
            if (M[i][j] == 'E') {
                s = i * c + j;
            }
            if (M[i][j] == 'D') {
                e = i * c + j;
            }
        }
    }
    //cout << "read com\n"; 
    ll tot = 0;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            if (M[i][j] != ' ') continue;
            for (int z = 0; z < 4; z ++) {
                int x = i + movs[z][0], y = j + movs[z][1];
                if (x >= 0 && x < r && y >= 0 && y < c && M[x][y] == ' ') {
                    cnt[i][j] ++;
                }
            }
            tot += cnt[i][j];
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    vector<int> vis(r*c, 0), sh(r*c, 1e9);
    int ans = -1;
    //cout << "e is " << e << endl;
    //cout << "total is "<< tot << endl;
    while (!pq.empty()) {
        int d, u; 
        pair<int, int> v = pq.top(); pq.pop();
        d = v.first; u = v.second;
        //cout << d << " " << u << endl;
        if (d > sh[u]) continue;
        vis[u] = 1;
        if (u == e) {
            ans = d;
            break;
        }
        int i = u / c, j = u % c;
        for (int z = 0; z < 4; z ++) {
            int x = i + movs[z][0], y = j + movs[z][1];
            if (x >= 0 && x < r && y >= 0 && y < c) {
                if (vis[x*c+y]) continue;
                if (M[x][y] == ' ') {
                    pq.push({d + cnt[x][y], x*c+y});
                }
                if (x*c+y == e) {
                    pq.push({d, x*c+y});
                }
            }
        }
    }
    double answer = (double)ans / tot;
    printf("%.6f", answer);
}