#include <bits/stdc++.h>
#define MAXN 105
using namespace std;
typedef tuple<int, int, double> iii;

double amt[MAXN], newamt[MAXN];
int main() {
    int t; cin >> t;
    while (t--) {
        int n,e,t; cin >> n >> e >> t;
        vector<unordered_set<int>> adj(n);
        for (int i = 0; i < n; i++) cin >> amt[i], newamt[i] = amt[i];
        vector<iii> edges;
        for (int i = 0; i < e; i++) {
            int src, dst;
            double p; cin >> src >> dst >> p;
            adj[src].insert(dst), adj[dst].insert(src);
            edges.push_back({src, dst, p});
        }
        for (int iter = 0; iter < t ; iter++) {
            for (int j = 0; j < e; j++) {
                int src, dst;
                double p;
                tie(src,dst,p) = edges[j];
                newamt[dst] += amt[src] * p;
                newamt[src] -=  amt[src] * p;
            }
            for (int i = 0; i < n; i++) amt[i] = newamt[i];
        }
        double mans = 10000000.0;
        for (int i = 0; i < n; i++) {
            double tot = amt[i];
            for (auto &j : adj[i]) tot += amt[j];
            mans = min(mans, tot);
        }
        cout << fixed << setprecision(6) << mans << '\n';
    }
}