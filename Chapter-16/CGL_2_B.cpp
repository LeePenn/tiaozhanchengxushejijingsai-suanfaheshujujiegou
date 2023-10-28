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
int T;
static const int COUNTER_CLOCKWISE = -1;
static const int CLOCKWISE = 1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    
    Point operator + (Point rh) {
        return {x + rh.x, y + rh.y};
    }
    
    Point operator - (Point rh) {
        return {x - rh.x, y - rh.y};
    }
    
    Point operator * (double a) {
        return {x * a, y * a};
    }
    
    double norm() {
        return x * x + y * y;
    }
}p1, p2, p3, p4;

struct Segment {
    Point p1, p2;
}s1, s2;
typedef Point Vector;

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool isEqual(double a, double b) {
    return fabs(a - b) < EPS;
}

Point Projection(Segment s, Point p) {
    Point p1 = s.p1, p2 = s.p2;
    Vector base = {p1.x - p2.x, p1.y - p2.y}, hypo = {p.x - p1.x, p.y - p1.y};
    
    double v = dot(base, hypo) / base.norm();
    return {s.p1.x + base.x * v, s.p1.y + base.y * v};
}

Point Reflection(Segment s, Point p) {
    return p + (Projection(s, p) - p) * 2.0;
}

int CCW(Point p1, Point p2, Point p3) {
    Vector v1 = p2 - p1, v2 = p3 - p1;
    if (cross(v1, v2) > EPS) return COUNTER_CLOCKWISE;
    if (cross(v1, v2) < -EPS) return CLOCKWISE;
    if (dot(v1, v2) < -EPS) return ONLINE_BACK;
    if (v1.norm() < v2.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}

bool Intersect(Point p1, Point p2, Point p3, Point p4) {
    return (CCW(p1, p2, p3) * CCW(p1, p2, p4) <= 0 && 
            CCW(p3, p4, p1) * CCW(p3, p4, p2) <= 0);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    while (T--) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y, &p4.x, &p4.y);
        s1.p1 = p1, s1.p2 = p2;
        s2.p1 = p3, s2.p2 = p4;
        printf("%d\n", Intersect(s1.p1, s1.p2, s2.p1, s2.p2));
    }
    
    return 0;
}
