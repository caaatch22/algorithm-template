#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

namespace Geometry {
using point = pair<double, double>;
double cross(const point&op, const point&sp, const point& ep) {
    return (sp.fi - op.fi) * (ep.se - op.se)
    - (sp.se - op.se) * (ep.fi - op.fi);
}

bool crossLeft(const point&op, const point&sp, const point&ep) {
    return (sp.fi - op.fi) * (ep.se - op.se)
    <= (sp.se - op.se) * (ep.fi - op.fi);
}

double dist2(const point& p, const point& q) {
    double x = q.fi - p.fi, y = q.se - p.se;
    return x * x + y * y;
}


double dist(const point& p, const point& q) {
    double x = q.fi - p.fi, y = q.se - p.se;
    return sqrt(x * x + y * y);
}

vector<point> convexHull(vector<point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    vector<point> q(n + 1);
    int top = 0;
    for (int i = 0; i < n; i ++) {
        while(top > 1 && crossLeft(q[top - 1], p[i], q[top - 2])) --top;
        q[top++] = p[i];
    }
    int len = top;
    for (int i = n - 2; i >= 0; --i) {
        while(top > len && crossLeft(q[top - 1], p[i], q[top - 2])) -- top;
        q[top++] = p[i];
    }
    top -= n > 1;
    q.resize(top);
    return q;
}

double diameter(vector<Point> p) {
    auto q = convexHull(p);
    if (q.size() < 2)  return 0;
    if (q.size() == 2)
        return dist2(q[0], q[1]);
    int n = (int)q.size();
    q.emplace_back(q[0]);
    double ans = 0;
    for (int i = 0, j = 2; i < n; ++i) {
        while (cross(q[i], q[i + 1], q[j]) < cross(q[i], q[i + 1], q[j + 1]))
            j = (j + 1) % n;
        ans = max({ans, dist2(q[i], q[j]), dist2(q[i + 1], q[j])});
    }
  return sqrt(ans);
} // float version: https://www.luogu.com.cn/problem/P6247
// Int version: https://www.luogu.com.cn/problem/P1452

double minDist(vector<point> a) {
    double d = 1e18;
    int n = (int)a.size();
    if(n <= 1) return d;
    sort(a.begin(), a.end());
    function<void(int, int)> merge = [&](int l, int r) {
        if(r - l <= 1)  return;
        if(r - l == 2) {
            d = min(d, dist(a[l], a[l + 1]));
            return;
        }
        int mid = (l + r) / 2;
        merge(l, mid);
        merge(mid + 1, r);
        vector<point> p;
        for (int i = m - 1; i >= l && a[m].fi - a[i].fi < d; --i) {
            p.emplace_back(a[i].se, a[i].fi);
        }
        for (int i = m; i < r && a[m].fi - a[i].fi < d; ++i) {
            p.emplace_back(a[i].se, a[i].fi);
        }
        sort(p.begin(), p.end());
        for (int i = 0, np = (int)p.size(); i < np; i ++) {
            for (int j = i + 1; j < np && p[j].fi - p[i].fi < d; ++j) {
                d = min(d, dist(p[i], p[j]));
            }
        }
    };
    merge(0, n);
    return d;
}

} //namespace Geometry