#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
int main() {
    int tc; cin >> tc;
    while (tc --) {
        ll F; int E; cin >> F >> E;
        if (E==0) {
            cout << F-1 << " " << F-1 << endl;
            continue;
        }
        ii floors[100000]; 
        ll d[101][101], last[100];
        int cnt = 0;
        memset(last, -1, sizeof last);
        memset(d, 31, sizeof d);
        for (int i = 0; i < E; i ++) {
            int m, r;cin >> r >> m;
            for (int j = r; j < F; j += m) {
                floors[cnt] = {j, i};
                cnt ++;
            } 
            d[E][i] = r; d[i][E] = r;
        }
        //E is the dummy for floor
        sort(floors, floors+cnt);
        for (int i = 0; i < cnt; i ++) {
            int el = floors[i].second;
            last[el] = floors[i].first;
            for (int j = 0; j < E; j ++) {
                if (last[j]<0) continue;
                d[el][j] = min(d[el][j], floors[i].first - last[j]);
                d[j][el] = d[el][j];
            }
        }
        for (int k = 0; k <= E; k ++) {
            for (int i = 0; i <= E; i ++) {
                for (int j = 0; j <= E; j ++ ) {
                    if (d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }
        int mlen = 0, floor = 0;

        for (int i = 0; i < cnt; i++) {
            if (i == 0) {
                int d1 = 0, d2 = d[E][floors[i].second];
                int x = (floors[i].first + d2 - d1) / 2;
                if (x  + d1 > mlen) mlen = x + d1, floor = x;   
            } else {
                int d1 = d[E][floors[i - 1].second], d2 = d[E][floors[i].second];
                int x = (floors[i].first - floors[i - 1].first + d2 - d1) / 2;
                if (x  + d1 > mlen) mlen = x + d1, floor = floors[i - 1].first + x;
            }
        }
        if (F - 1 - floors[cnt - 1].first + d[E][floors[cnt-1].second] > mlen) {
            mlen = F - 1 - floors[cnt - 1].first + d[E][floors[cnt-1].second];
            floor = F-1;
        }
        cout << mlen << " " << floor << endl;


    }
}