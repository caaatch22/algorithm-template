#include<bits/stdc++.h>
using namespace std;
// return p, p[i]表示修改后的串中以i为中心的最长回文半径
vector<int> manacher(const string& _s) {
    vector<int> p(_s.size() * 2 + 1);
    string s(_s.size() * 2 + 1, '$');
    for (int i = 0; i < _s.size(); i++) s[2 * i + 1] = _s[i];
    for(int i = 0, maxr = 0, mid = 0; i < s.size(); i++) {
        if(i < maxr) p[i] = min(p[mid * 2 - i], maxr - i);
        while(i - p[i] - 1 >= 0 && i + p[i] + 1 < s.size() 
            && s[i - p[i] - 1] == s[i + p[i] + 1]) 
            ++p[i];
        if(i + p[i] > maxr) maxr = i + p[i], mid = i;
    }
    return p;
}


int main() {
    string s;
    cin >> s;
    auto p = manacher(s);
    // for (int i = 0; i < p.size(); i ++) {
    //     cout << p[i] << " \n"[i == p.size() - 1];
    // }
    cout << (*max_element(p.begin(), p.end())) << endl;
}