#pragma warning(disable: 4996)

#include <cmath>
#include <algorithm>
#include <iostream>
#include <regex>
#include <string.h>
#include <queue>
#include <unordered_map>

using namespace std;

struct jump {
    int x, y, cost;
};

const int INF = 1000000000; // INF = 1B, not 2^31-1 to avoid overflow
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ii> vii;

int n, m, ct, g, x, y, h, x1, y2, c;
vector<vi> mapp, dist;
vector<vector<vector<jump>>> edges;
vector<vi> d{ {0,1}, {1,0},{0,-1},{-1,0} };

int lsone(int l) {
    return l& (-1 * l);
}

bool isInside(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
    ios_base::sync_with_stdio(false);
    while (true) {
        cin >> n >> m;
        if (n == 0) {
            break;
        }
        edges.assign(n, vector<vector<jump>>(m, vector<jump>{}));
        mapp.assign(n, vi( m, 0 ));
        cin >> g;
        for (int i = 0; i < g; i++) {
            cin >> x >> y;
            mapp[x][y] = -1;
        }
        cin >> h;
        for (int i = 0; i < h; i++) {
            cin >> x >> y >> x1 >> y2 >> c;
            mapp[x][y] = i + 1;
            edges[x][y].push_back(jump{ x1,y2,c });
        }
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                int id = mapp[x][y];
                if (id != 0 || (x == n - 1 && y == m - 1)) {
                    continue;
                }
                for (vi l : d) {
                    int xx = x + l[0];
                    int yy = y + l[1];
                    if (isInside(xx, yy) && mapp[xx][yy] >= 0) {
                        edges[x][y].push_back(jump{ xx,yy,1 });
                    }
                }
            }
        }
        dist.assign(n, vi( m, INF ));
        dist[0][0] = 0;
        for (int i = 0; i < n * m; i++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    if (dist[x][y] == INF) {
                        continue;
                    }
                    for (jump lll : edges[x][y]) {
                        int xx = lll.x;
                        int yy = lll.y;
                        int cost = lll.cost;
                        if (dist[x][y] + cost < dist[xx][yy]) {
                            dist[xx][yy] = dist[x][y] + cost;
                        }
                    }
                }
            }
        }
        bool neg_loop = false;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (dist[x][y] == INF) {
                    continue;
                }
                for (jump lll : edges[x][y]) {
                    int xx = lll.x;
                    int yy = lll.y;
                    int cost = lll.cost;
                    if (dist[x][y] + cost < dist[xx][yy]) {
                        neg_loop = true;
                        goto out;
                    }
                }
            }
        }
        out: if (neg_loop) {
            cout << "Never" << endl;
        }
        else if (dist[n - 1][m - 1] == INF) {
            cout << "Impossible" << endl;
        }
        else {
            cout << dist[n - 1][m - 1] << endl;
        }
    }
}