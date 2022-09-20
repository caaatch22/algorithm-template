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

{
    // using std::tie for multi key compare in structure:
    struct Node{
        int x, y, z;
        bool operator<(const Node& rhs) const {
            return tie(x, y, z) < tie(rhs.x, rhs.y, rhs.z);
        }
    };
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

    // sum of k largest numbers in linear time
    nth_element(a.begin(), a.end(), k);
    ll ans = accumulate(a.begin(), a.begin() + k, 0LL);

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

    count(v.begin(), v.end(), target);
    count_if(v.begin(), v.end(), [](int x) {x % 4 == 0});


    // 常用在分治中的一些STL: inplace_merge, merge, partition, stable_partition
    // Merges two consecutive sorted ranges [first, middle) and [middle, last)
    // into one sorted range [first, last).
    void inplace_merge(BidirIt first, BidirIt middle, BidirIt last);
    // example
    template<class Iter>
    void merge_sort(Iter first, Iter last) {
        if (last - first > 1) {
            Iter middle = first + (last - first) / 2;
            merge_sort(first, middle);
            merge_sort(middle, last);
            std::inplace_merge(first, middle, last);
        }
    }
    // used in merge, cdq

    // partition, 将满足条件p的元素放在前部分
    template <class ForwardIt, class UnaryPredicate>
    constexpr ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p);

    // partition的stable版本，常在分支中使用
    template <class BidirIt, class UnaryPredicate>
    BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPredicate p);

    #include <algorithm>
    #include <array>
    #include <iostream>
    
    int main()
    {
        std::array<int, 9> v{};
        std::iota(v.begin(), v.end(), 1);

        auto is_even = [](int i){ return i % 2 == 0; };
        std::cout.setf(std::ios_base::boolalpha);
        std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
    
        std::partition(v.begin(), v.end(), is_even);
        std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
    
        std::reverse(v.begin(), v.end());
        std::cout << std::is_partitioned(v.cbegin(), v.cend(), is_even) << ' ';
        std::cout << std::is_partitioned(v.crbegin(), v.crend(), is_even) << '\n';
        // output:
        // false true false true
    }
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

    string to_string(/*numeric type*/);

    //将字符串按照字面转化为数字类型
    int stoi(const string &str);
    long long stoll(const string &str);
    float stof(const string &str);
    double stod(const string &str);
    long double stold(const string &str);
    
}

int main() {
}