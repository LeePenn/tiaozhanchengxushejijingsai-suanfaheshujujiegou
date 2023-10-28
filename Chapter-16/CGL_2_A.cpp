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
int n;
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
}p[5];
typedef Point Vector;
Vector v1, v2;

bool isEqual(double a, double b) {
    return fabs(a - b) < EPS;
}

double dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

double cross(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

bool isOrthogonal(Vector v1, Vector v2) {
    return isEqual(dot(v1, v2), 0.0);
}

bool isParallel(Vector v1, Vector v2) {
    return isEqual(cross(v1, v2), 0.0);
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
    while (n--) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &p[1].x, &p[1].y, &p[2].x, &p[2].y, &p[3].x, &p[3].y, &p[4].x, &p[4].y);
        
        Vector v1 = {p[1].x - p[2].x, p[1].y - p[2].y}, 
        v2 = {p[3].x - p[4].x, p[3].y - p[4].y};
        
        if (isOrthogonal(v1, v2)) {
            printf("1\n");
        } else if (isParallel(v1, v2)) {
            printf("2\n");
        } else printf("0\n");
    }
    
    
    return 0;
}
