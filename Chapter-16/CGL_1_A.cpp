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
const double EPS = 1e-10;
int q;
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    
    double norm() {
        return x * x + y * y;
    }
}a, b, c;

struct Segment {
    Point p1, p2;
}s;
typedef Point Vector;

bool isEqual(double a, double b) {
    return fabs(a - b) < EPS;
}

double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
    s.p1 = a, s.p2 = b;
    scanf("%d", &q);
    while (q--) {
        scanf("%lf%lf", &c.x, &c.y);
        
        Vector base = {a.x - b.x, a.y - b.y}, hypo = {c.x - a.x, c.y - a.y};
        
        double v = dot(base, hypo) / base.norm();
        printf("%.10f %.10f\n", s.p1.x + base.x * v, s.p1.y + base.y * v);
    }
    
    
    return 0;
}
