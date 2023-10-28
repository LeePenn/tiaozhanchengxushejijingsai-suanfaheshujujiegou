#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 100000 + 5, M = 60000 + 5, INF = 1000000000;
int n, m;
struct Edge {
    int v, nxt;
    Edge() {}
    Edge(int v, int nxt): v(v), nxt(nxt) {}
}edge[N << 1];
int hd[N], tot, dfn[N], low[N], pa[N], tm;
bool vis[N];

void add_edge(int u, int v) {
    edge[++tot] = Edge(v, hd[u]);
    hd[u] = tot;
}

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++tm;
    vis[u] = 1;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        
        if (!vis[v]) {
            pa[v] = u;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u , v); add_edge(v, u);
    }
    
    memset(vis, 0, sizeof(vis));
    dfs(0, -1);
    
    set<int> ans;
    int np = 0;
    for (int i = 1; i < n; ++i) {
        int p = pa[i];
        if (p == 0) np++;
        else if (dfn[p] <= low[i]) ans.insert(p);
    }
    
    if (np > 1) ans.insert(0);
    for (set<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
        printf("%d\n", *it);
    }
    
    return 0;
}
