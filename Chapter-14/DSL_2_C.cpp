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
const int N = 1000000 + 5, M = 60000 + 5, INF = 1000000000;
int n, q;
struct Node {
    int p, l, r;
    int location;
    Node() {}
};

struct Point {
    int id, x, y;
    Point() {}
    Point(int id, int x, int y): id(id), x(x), y(y) {}
    
    bool operator <(const Point &rh) const {
        return id < rh.id;
    }
    
    void print() {
        printf("%d\n", id);
    }
};
Point P[N];
Node T[N];
int tot;

bool lessX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

bool lessY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

int Build(int l, int r, int d) {
    if (l > r) return 0;
    
    int t = ++tot;
    int mid = (l + r) >> 1;
    
    if (d % 2 == 0) sort(P + l, P + r + 1, lessX);
    else sort(P + l, P + r + 1, lessY);
    
    T[t].location = mid;
    T[t].l = Build(l, mid - 1, d + 1);
    T[t].r = Build(mid + 1, r, d + 1);
    
    return t;
}

void Find(int u, int sx, int tx, int sy, int ty, int d, vector<Point> &ans) {
    int x = P[T[u].location].x, y = P[T[u].location].y;
    
    if (sx <= x && x <= tx && sy <= y && y <= ty) {
        ans.push_back(P[T[u].location]);
    }
    
    if (d % 2 == 0)  {
        if (T[u].l != 0) {
            if (sx <= x) Find(T[u].l, sx, tx, sy, ty, d + 1, ans);
        }
        if (T[u].r != 0) {
            if (x <= tx) Find(T[u].r, sx, tx, sy, ty, d + 1, ans);
        }
    } else {
        if (T[u].l != 0) {
            if (sy <= y) Find(T[u].l, sx, tx, sy, ty, d + 1, ans);
        }
        if (T[u].r != 0) {
            if (y <= ty) Find(T[u].r, sx, tx, sy, ty, d + 1, ans);
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
    
    scanf("%d", &n);
    int x, y;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &x, &y);
        P[i] = Point(i - 1, x, y);
        T[i].l = T[i].r = T[i].p = 0;
    }
    
    tot = 0;
    int rt = Build(1, n, 0);
    
    scanf("%d", &q);
    int sx, tx, sy, ty;
    vector<Point> ans;
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d%d%d", &sx, &tx, &sy, &ty);
        ans.clear();
        Find(rt, sx, tx, sy, ty, 0, ans);
        
        sort(ans.begin(), ans.end());
        for (size_t j = 0; j < ans.size(); ++j) {
            ans[j].print();
        }
        printf("\n");
    }
    
    
    return 0;
}
