#include <bits/stdc++.h>
using ll = long long;
using namespace std;

/*
lambda expression
*/

/* structure binding */
{   
    // Graph with weighted edges
    vector<vector<pair<int, int>>> G(n);
    // somewhere in dfs, 
    for (auto [v, w] : G[u]) {
        ...
    }
}

/* discrete manipulate*/
{
    // vector<int> v. vv = v;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

}

/*
some useful function in STL
*/
{
    int n = 256;
    vector<int> v(n);
    // generate v as 0, 1, 2, ...
    // often used when you initialize DSU or generate a permutation
    iota(v.begin(), v.end(), 0);

    ll res = accumulate(v.begin(), v.end(), 1LL, 
                        [](int a, int b){return (ll)a*b;});

    gcd() and lcm(); // not __gcd() version

    // max_element and min_element which can be used with user-defined op
    cout << *max_element(v.begin(), v.end() /*[]()->bool{}*/);

    //std::clamp
    // Returns x if it is in the interval [low, high] or, 
    // otherwise, the nearest value.No more max of min of max of...
    cout << clamp(7, 0,  10); //7
    cout << clamp(7, 0,  5);  //5
    cout << clamp(7, 10, 50); //10

    /*don't do*/ max(ans, max(t1, t2));
    /*just*/ max({ans, t1, t2}); // initalizer list


    /* partial_sum and adjacent_difference 前缀和与差分 */
    vector<int> a(n, 2), b(n, 2);
    partial_sum(a.begin(), a.end(), a.begin());
    partial_sum(a.begin(), a.end(), b.begin());

    adjacent_difference(v.begin(), v.end(), v.begin());
}

/*
template< class R, class... Args >
class function<R(Args...)>;
*/
{
    // a callable obj
    function<int(int, int)> dfs = [&](int u, int fa) {
        ...
    };
}

/* Set operations (on sorted ranges)*/
{
    set<int> s1, s2;
    set<int> ans;
    set_intersection(s1.begin(), s1.end(),
                          s2.begin(), s2.end(),
                          std::inserter(ans, ans.begin()));
                          // 若为vector， 可以用back_inserter;
}

/*
Initializer in if and switch:
*/
{
    set<int> s;
    if (auto [iter, ok] = s.insert(42); ok) {
        //...
    }
    else {
        //`ok` and `iter` are available here
    }
    //But not here
}

/*
about string
*/
{
    substr(npos, count);
}

int main() {
}