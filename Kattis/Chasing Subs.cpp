#include <bits/stdc++.h>
using namespace std;
#define MAX_N 251000

int b[MAX_N];


void kmppreprocess(string &P) {
    int m = P.size();
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while ((j >= 0) && P[i] != P[j]) j = b[j];
        ++j; ++i;
        b[i] = j;
    }
}

unordered_map<int , int> matching;

int kmpsearch(string &P, string &T) {
    // printf("comaring %s %s\n", P.c_str(), T.c_str());
    int n = T.size(), m = P.size();
    int freq = 0;
    int i = 0, j = 0;
    while ( i < n) {
        while ((j >= 0 && T[i] != P[j])) j = b[j];
        ++i; ++j;
        if (j == m) {
            ++freq;
            matching[i-j]++;
            // printf("P is found at index %d in T\n", i - j);
            j = b[j];
        }
    }
    return freq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string text, pat; cin>>text>>pat;
    int n = text.size(), m = pat.size();
    

    string aa , bb;
    for (int i = 0; i < n ;i++) aa += '0';
    for (int i = 0; i < m ;i++) bb += '0';
    


    vector<string> textbin(26, aa);
    vector<string> patbin(26, bb);

    for (int i = 0; i < n; i++) {
        textbin[text[i] - 'a'][i] = '1';
    }
    for (int i = 0; i < m; i++) {
        patbin[pat[i] - 'a'][i] = '1';
    }

    // for (int i = 0; i < 5; i++) {
    //     cout<<textbin[i]<<endl;
    //     cout<<patbin[i]<<endl;
    // }
    
    int freqpat[26] = {0};
    int freqtext[26] = {0};
    for (int i = 0; i < n; i++) freqtext[text[i] - 'a'] ++;
    for (int i = 0; i < m; i++) freqpat[pat[i] - 'a'] ++;


    int numchar_p = 0;
    int numchar_t = 0;
    for (int i =0; i < 26; i++) {
        if (freqtext[i]) numchar_t++;
        if (freqpat[i]) numchar_p++;

    }
    // if (numchar_p != numchar_t) {
    //     cout << "0"; 
    // }

    for (int i = 0; i < 26; i++) {
        if (!freqpat[i]) continue;
        kmppreprocess(patbin[i]);
        for (int j  = 0 ; j < 26; j++) {
            if (!freqtext[j]) continue;
            kmpsearch(patbin[i], textbin[j]);    
        }
    }

    int num = 0; int pos;
    for (int i = 0; i < n; i++) {
        // printf("pos %d, %d matchings\n", i , matching[i]);
        if (matching[i] == numchar_p) {
            pos = i; num++;
        }
    }
    if (num == 1) cout<<text.substr(pos, m);
    else cout<<num;



}