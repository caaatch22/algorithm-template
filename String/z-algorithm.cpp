//给定两个字符串 a,b，
// 要求出两个数组：b的z函数数组z、
// b与a的每一个后缀的LCP长度数组p。
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i ++)
#define sz(a) int((a).size())
using namespace std;
using ll = long long;
const int N = 2e7;
ll ansz, ansp;
string a, b;

// Zfunction
int z[N << 1];
void getz(string s) {
    int l = 0;
    for (int i = 1; i <= s.size(); i ++) {
        if(l + z[l] > i) z[i] = min(z[i - l], l + z[l] - i);
        while(i + z[i] < s.size() && s[z[i]] == s[i + z[i]])  z[i]++;
        if(i + z[i] > l + z[l]) l = i;
    }
    // rep(i,0,s.size()) cout<<z[i]<<" ";cout<<'\n';
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> a >> b, getz(b + a);
    ansz ^= 1ll * (sz(b)+1)*(0+1);
    rep(i,1,sz(b)) ansz^=1ll*(min(z[i],sz(b)-i)+1)*(i+1);
    rep(i,0,sz(a)) ansp^=1ll*(min(z[i+sz(b)],sz(b))+1)*(i+1);
    cout << ansz << '\n'
         << ansp << '\n';
    return 0;
}