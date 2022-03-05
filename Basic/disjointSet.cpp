//acwing837 
//basic disjoint-set 
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int fa[N], w[N], n, m;

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main()
{
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) fa[i] = i, w[i] = 1;
        
    while(m -- )
    {
        char op[3];
        int x, y;
        cin >> op >> x;
        if(!strcmp(op, "C"))
        {
            cin >> y;
            if(find(x) != find(y))
            {
                w[find(y)] += w[find(x)];
                fa[find(x)] = find(y);
            }
        }
        else if(!strcmp(op, "Q1"))
        {
            cin >> y;
            if(find(x) == find(y)) cout << "Yes\n"; else cout << "No\n";
        }
        else 
        {
            cout << w[find(x)] << '\n';
        }
    }
    
    return 0;
}