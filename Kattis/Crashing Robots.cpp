#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int moves[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int r,c, n, ins;
int M[105][105];
vector<ii> loc;
vector<int> dirs;
int main() {
    int tc; cin >> tc;
    while (tc --) {
        cin >>c >> r >> n >> ins;
        loc.resize(n+5);
        dirs.resize(n+5);
        memset(M, -1, sizeof M);
        for (int i = 1; i <= n; i ++) {
            cin >> loc[i].second >> loc[i].first;
            M[loc[i].first][loc[i].second] = i;
            string s; cin >> s;
            if (s == "N") dirs[i] = 0;
            if (s == "E") dirs[i] = 1;
            if (s == "S") dirs[i] = 2;
            if (s == "W") dirs[i] = 3;
        }
        bool fail = false;
        for (int i = 0; i < ins; i ++) {
            int id; cin >> id;
            string s; cin >> s;
            int rep; cin >> rep;
            if (fail) continue;
            if (s == "L") {
                dirs[id] = ((dirs[id] - rep) % 4 + 4) % 4;

            }
            if (s == "R") {
                dirs[id] = (dirs[id] + rep) % 4;
            }
            if (s == "F") {
                int x = loc[id].first, y = loc[id].second;
                int nx = x + rep * moves[dirs[id]][0], ny = y + rep * moves[dirs[id]][1];

                for (int i = 1; i <= rep; i ++) {
                    int nnx = x + i * moves[dirs[id]][0];
                    int nny = y + i * moves[dirs[id]][1];

                    //cout << nnx << " " << nny << " " << M[nnx][nny] << endl;
                    if (nnx <= 0 || nnx > r || nny <= 0 || nny > c) {
                        cout << "Robot " << id <<" crashes into the wall\n";\
                        fail = true;
                        break;
                    }
                    if (M[nnx][nny]!=-1) {
                        cout << "Robot " << id << " crashes into robot " << M[nnx][nny] << endl;
                        fail = true;
                        break;
                    }
                }
                if (!fail) {
                    M[x][y]= -1;
                    M[nx][ny] = id;
                    loc[id] = {nx,ny};
                    //cout << id << " now at " << nx << " " << ny << endl;
                }
            }
        }
        if (!fail) {
            cout << "OK\n";
        }
    }
}