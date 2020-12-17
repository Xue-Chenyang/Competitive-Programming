#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;


struct Per {
    int amt, idx;
};
bool operator<(Per a, Per b) {
    if (a.amt != b.amt) return a.amt > b.amt;
    return a.idx < b.idx;
}

int main() {

    int tc; cin>>tc;
    while (tc--) {
        int p,n; cin>>p>>n;
        vector<Per> pers(n);
        for(int i =0; i <n; i++) {
            int amt; cin>>amt;
            pers[i].amt = amt;
            pers[i].idx = i;
        }

        sort(pers.begin(), pers.end());

        vector<ii> step;
        step.push_back({pers[n-1].amt, n});
        //printf("Step %d %d\n", pers[n-1].amt, n);
        int level = step[0].first;
        int i = n-1;
        while (1) {
            while (i >= 0 && pers[i].amt == level) i--;
            if (i < 0) break;
            //printf("Step %d, %d\n", pers[i].amt - level, i + 1);
            step.push_back({pers[i].amt - level, i + 1});
            
            level = pers[i].amt;
        
        
        }
        
        int tot = 0;

        vector<int> paid(n,0);

        for (auto it: step) {
            int lvl,num; tie(lvl, num) = it;
            int left = p - tot;
            if (lvl * num < left) {
                for (int i = 0; i < num; i++) paid[i] += lvl;
                tot += lvl * num;
            } else {
                int q = left / num, r = left % num;
                for (int i = 0; i < num; i++) paid[i] += q;
                for (int i = 0; i < r; i++) paid[i]++;
                tot += left;
                break;
            }
        }
        if (tot < p) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        vector<int> ans(n,0);
        for (int i = 0; i < n; i++) {
            ans[pers[i].idx] = paid[i];
        }

        for (auto it: ans) cout<<it<<" "; cout<<endl;
    }
}