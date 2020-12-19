#include <bits/stdc++.h>
using namespace std;

int main() {
    cout<<1<<endl;
    int cur = 1;
    srand(time(NULL));
    while (cin>>cur) {
        if (cur == 99) return 0;

        if (cur % 3 == 2) cur++;
        else if (cur % 3 == 0) {
            cur += 1 + (rand() % 2);
        }
        else cur += 2;

        cout<<cur << endl;
        if (cur == 99) return 0;
    }

}