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
int T, n;
static const int COUNTER_CLOCKWISE = -1;
static const int CLOCKWISE = 1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
static const int LEFT = 1;
static const int BOTTOM = 0;
static const int RIGHT = 2;
static const int TOP = 3;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    
    bool operator < (const Point &rh) const{
        return x < rh.x || (fabs(x - rh.x) < EPS && y < rh.y);
    }
    
    Point operator + (Point rh) {
        return {x + rh.x, y + rh.y};
    }
    
    Point operator - (Point rh) {
        return {x - rh.x, y - rh.y};
    }
    
    Point operator * (double a) {
        return {x * a, y * a};
    }
    
    Point operator / (double a) {
        return {x / a, y / a};
    }
    
    double norm() {
        return x * x + y * y;
    }
    
    double abs() {
        return sqrt(x * x + y * y);
    }
};

struct Segment {
    Point p1, p2;
}s[100000 + 10];
struct Line {
    Point p1, p2;
};
typedef Point Vector;

struct Circle {
    Point c;
    double r;
}c1, c2;

struct Polygon {
    Point p[100000 + 5];
}poly;

struct EndPoint {
    Point p;
    int seg, st;
    EndPoint() {}
    EndPoint(Point p, int seg, int st): p(p), seg(seg), st(st) {}
    
    bool operator < (const EndPoint &ep) const {
        if (p.y == ep.p.y) {
            return st < ep.st;
        } else return p.y < ep.p.y;
    }
}EP[2 * 100010];

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

Point CrossPoint(Point p1, Point p2, Point p3, Point p4) {
    Vector base = p2 - p1;
    double d1 = fabs(cross(p3 - p1, base)), d2 = fabs(cross(p4 - p1, base));
    double t = d1 / (d1 + d2);
    return p3 + (p4 - p3) * t;
}

pair<Point, Point> getCrossPoints(Circle c, Line l) {
    Vector base = l.p2 - l.p1;
    Vector e = base / base.abs();
    Segment s = {l.p1, l.p2};
    Point t = Projection(s, c.c);
    Point pr = t - c.c;
    double r = sqrt(c.r * c.r - pr.norm());
    return make_pair(t - e * r, t + e * r);
}

double getDistanceLP(Segment l, Point p) {
    Point p1 = l.p1, p2 = l.p2;
    Vector base = p2 - p1;
    return abs(cross(base, p - p1) / base.abs());
}

double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return (p - s.p1).abs();
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return (p - s.p2).abs();
    return getDistanceLP(s, p);
}

double getDistance(Segment s1, Segment s2) {
    if (Intersect(s1.p1, s1.p2, s2.p1, s2.p2)) return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)), 
            min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

double arg(Vector p) {
    return atan2(p.y, p.x);
}

// 投影向量
Vector polar(double a, double r) {
    return {cos(r) * a, sin(r) * a};
}

pair<Point, Point> getCircleCrossPoints(Circle c1, Circle c2) {
    double d = (c1.c - c2.c).abs();
    // theta 夹角
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    // x axis 夹角
    double t = arg(c2.c - c1.c);
    return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}

int Contain(Polygon poly, Point p) {
    bool flag = false;
    for (int i = 1; i <= n; ++i) {
        Point a = poly.p[i] - p, b = poly.p[(i % n) + 1] - p;
        if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && b.y > EPS && cross(a, b) > EPS) flag = !flag;
    }
    return (flag ? 2 : 0);
}

vector<Point> AndrewScan(Polygon poly) {
    vector<Point> ans;
    if (n < 3) {
        for (int i = 1; i <= n; ++i) {
            ans.push_back(poly.p[i]);
        }
        return ans;
    }
    
    vector<Point> u, l;
    sort(poly.p + 1, poly.p + n + 1);
    // for (int i = 1; i <= n; ++i) {
    //     printf("! %d %d\n", (int)poly.p[i].x, (int)poly.p[i].y);
    // }
    
    u.push_back(poly.p[1]);
    u.push_back(poly.p[2]);
    
    l.push_back(poly.p[n]);
    l.push_back(poly.p[n - 1]);
    
    for (int i = 3; i <= n; ++i) {
        while (u.size() >= 2 && (CCW(u[u.size() - 2], u[u.size() - 1], poly.p[i]) != CLOCKWISE && CCW(u[u.size() - 2], u[u.size() - 1], poly.p[i]) != ONLINE_FRONT)) {
            u.pop_back();
        }
        u.push_back(poly.p[i]);
    }
    
    // for (size_t i = 0; i < u.size(); ++i) {
    //     printf("! %d %d\n", (int)u[i].x, (int)u[i].y);
    // }
    
    for (int i = n - 2; i >= 1; i--) {
        while (l.size() >= 2 && (CCW(l[l.size() - 2], l[l.size() - 1], poly.p[i]) != CLOCKWISE && CCW(l[l.size() - 2], l[l.size() - 1], poly.p[i]) != ONLINE_FRONT)) {
            // printf("## %d %d ## %d %d ## %d %d\n", 
            // (int)l[l.size() - 2].x, (int)l[l.size() - 2].y, (int)l[l.size() - 1].x, (int)l[l.size() - 1].y, (int)poly.p[i].x, (int)poly.p[i].y);
            l.pop_back();
        }
        l.push_back(poly.p[i]);
    }
    
    // for (size_t i = 0; i < l.size(); ++i) {
    //     printf("@ %d %d\n", (int)l[i].x, (int)l[i].y);
    // }
    
    reverse(l.begin(), l.end());
    for (size_t i = u.size() - 2; i >= 1; --i) {
        l.push_back(u[i]);
    }
    
    return l;
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
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &s[i].p1.x, &s[i].p1.y, &s[i].p2.x, &s[i].p2.y);
    }
    
    for (int i = 1, k = 0; i <= n; ++i) {
        if (s[i].p1.y == s[i].p2.y) {
            if (s[i].p1.x > s[i].p2.y) swap(s[i].p1, s[i].p2);
        } else if (s[i].p1.y > s[i].p2.y) swap(s[i].p1, s[i].p2);
        
        if (s[i].p1.y == s[i].p2.y) {
            EP[++k] = EndPoint(s[i].p1, i, LEFT);
            EP[++k] = EndPoint(s[i].p2, i, RIGHT);
        } else {
            EP[++k] = EndPoint(s[i].p1, i, BOTTOM);
            EP[++k] = EndPoint(s[i].p2, i, TOP);
        }
    }
    
    sort(EP + 1, EP + 2 * n + 1);
    set<int> BT;
    BT.insert(1000000001);
    int cnt = 0;
    
    for (int i = 1; i <= 2 * n; ++i) {
        if (EP[i].st == TOP) {
            BT.erase(EP[i].p.x);
        } else if (EP[i].st == BOTTOM) {
            BT.insert(EP[i].p.x);
        } else if ()
    }
    
    return 0;
}
