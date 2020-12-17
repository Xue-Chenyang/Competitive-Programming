#include <bits/stdc++.h>
using namespace std;

int main() {

    int r,c; cin>>r>>c;
    vector<int> rows,cols;
    rows.resize(r); cols.resize(c);
    for (auto &it: rows) cin>>it;
    for (auto &it: cols) cin>>it;
    
    vector<vector<int>> M;
    for (int i = 0; i < r; i ++) {
        M.push_back(vector<int>(c, rows[i]));
    }
    for (int i = 0; i < c; i ++) {
        bool ok = false;
        for (int j = 0; j < r; j ++) {
            M[j][i] = min(M[j][i], cols[i]);
            if (M[j][i] == cols[i]) ok = true;
        }
        if (!ok) {
          cout<<"impossible"; 
          return 0;
        }
    }
    for (int i = 0; i < r; i ++) {
        int m = 0;
        for (int j = 0; j < c; j ++) {
            m = max(m, M[i][j]);
        }
        if (m != rows[i]) {
          cout<<"impossible"; 
          return 0;
        }
    }
    cout << "possible";
}